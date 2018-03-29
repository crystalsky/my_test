#include "TaskManager.h"
#include <glog.h>
#include "TaskDataQueue.h"
#include "FileTransferTask.h"
#include "ClientsManager.h"
#include <boost/bind.hpp>

TaskManager::TaskManager(const IceUtil::Handle<ClientsManager>& ptrClientsManager)
	: _clientsManager(ptrClientsManager)
{
	assert(_clientsManager != NULL);

	_taskDataQueue = new TaskDataQueue(this);
	_taskDataQueue->start();

	if (_clientsManager)
	{
		_connection = _clientsManager->connectOnLoseConnection(
			boost::bind(&TaskManager::onClientLossConnection, this, _1));
	}
}

TaskManager::~TaskManager()
{
	_connection.disconnect();
	_taskDataQueue->destroy();
}

void TaskManager::setRecvDataPackage( 
	/*const ::DataTransmitter::AMD_DataProc_sendDataPtr& cb, */
	const ::DataTransmitter::SendDataPackagePtr& data )
{
	if (_taskDataQueue)
	{
		_taskDataQueue->addRecvData(/*cb, */data);
	}
}

bool TaskManager::checkTaskDataInfo( const ::DataTransmitter::CheckDataInfo& cdInfo )
{
	UserTaskPtr ptrTask = getTaskByTaskID(cdInfo.objTaskInfo->strTaskID);
	if (!ptrTask)
	{
		LOG(ERROR) << "No Task ID Of" << cdInfo.objTaskInfo->strTaskID;
		return false;
	}

	if (!ptrTask->isHasFinishedRecvData() ||
		!ptrTask->checkDataCRC(cdInfo.nTaskDataCRC))
	{
		//TODO do some thing resend work at here
		//it should be record the error package of the data
		//and send them to client and resend....
		std::string reason;
		if (!ptrTask->isHasFinishedRecvData())
		{
			reason = "数据没有接收完整...";
		}
		else
		{
			reason = "数据CRC验证不正确...";
		}

		LOG(ERROR)
			<< "\n	User:" << cdInfo.objTaskInfo->strTaskUser
			<< "\n  Task:" << cdInfo.objTaskInfo->strTaskID
			<< "\n	Recv Data Failed..."
			<< "\n	Reson:" << reason;

		return false;
	}
	finishTask(ptrTask);
	return true;
}

UserTaskPtr TaskManager::getTaskByTaskID( const std::string& strTaskID )
{
	MapTasks _tempAllTask;
	{
		IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
		_tempAllTask = _mapAllTasks;
	}

	MapTasks::iterator itFindTask =
		_tempAllTask.find(strTaskID);
	if (itFindTask != _tempAllTask.end())
	{
		return itFindTask->second;
	}
	return UserTaskPtr();
}

bool TaskManager::processUserDataInfo( const ::DataTransmitter::SendDataInfo& dataInfo )
{
	assert(_clientsManager != NULL);
	if (!_clientsManager)
	{
		LOG(ERROR) << "No Clients Manager....";
		return false;
	}
	if (!checkSendDataInfo(dataInfo))
	{
		return false;
	}

	MapTasks _tempAllTask;
	{
		IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
		_tempAllTask = _mapAllTasks;
	}
	
	MapTasks::iterator itFindTask =
		_tempAllTask.find(dataInfo.objTaskInfo->strTaskID);
	if (itFindTask != _tempAllTask.end())
	{
		LOG(WARNING) << "Has Task With ID:" << 
			dataInfo.objTaskInfo->strTaskID;
		return false;
	}
	
	Login::LoginCallBackPrx clientPtr = 
		_clientsManager->FindClientByID(dataInfo.objTaskInfo->strTaskUser);
	if (!clientPtr)
	{
		LOG(ERROR) << "No Clients Of ID:" << dataInfo.objTaskInfo->strTaskUser;
		return true;
	}

	UserTaskPtr newTask = createTask(clientPtr, dataInfo);
	
	{
		IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
		_mapAllTasks.insert(
			std::make_pair(dataInfo.objTaskInfo->strTaskID, newTask));
	}
	
	return true;
}

UserTaskPtr TaskManager::createTask( const Login::LoginCallBackPrx& clientPtr, const ::DataTransmitter::SendDataInfo& dataInfo )
{
	DataTransmitter::emTaskType tType = 
		dataInfo.objTaskInfo->taskType;

	UserTaskPtr ptrTask;
	switch (tType)
	{
	case DataTransmitter::TaskFileTransfer:
		{
			ptrTask.reset(new FileTransferTask(clientPtr));
		}
		break;
	case DataTransmitter::TaskTestDataRecv:
	case DataTransmitter::TaskCaculate:
	case DataTransmitter::TaskOther:
		{
			ptrTask.reset(new UserTask(clientPtr));
		}
		break;
	default:
		{
			LOG(WARNING) << "No Support TaskType...";
		}
		break;
	}

	if (ptrTask)
	{
		ptrTask->setDataInfo(dataInfo.objDataInfo);
		ptrTask->setTaskInfo(dataInfo.objTaskInfo);
		ptrTask->initialTaskAditionalInfo(dataInfo.additionalInfo);

		LOG(INFO)
			<< "\n	Client: [" << dataInfo.objTaskInfo->strTaskUser << "]"
			<< "\n	Task:["	<< dataInfo.objTaskInfo->strTaskID << "]"
			<< "\n	DataSize=[" << dataInfo.objDataInfo->nDataTotalSize << "]"
			<< "\n	EveryPackSize=[" << dataInfo.objDataInfo->nEveryPackSize << "]"
			<< "\n	PackCount=[" << dataInfo.objDataInfo->nPackageCount << std::endl;
	}

	return ptrTask;
}

bool TaskManager::checkSendDataInfo( const DataTransmitter::SendDataInfo& dataInfo ) const
{
	if (dataInfo.objTaskInfo->strTaskID.empty())
	{
		LOG(ERROR) << "Error Task With No TaskID...";
		return false;
	}
	else if (dataInfo.objDataInfo->nDataTotalSize <= 0 ||
		dataInfo.objDataInfo->nEveryPackSize <= 0 ||
		dataInfo.objDataInfo->nPackageCount <= 0)
	{
		LOG(ERROR) << "Error Task With DataInfo:"
			<< "DataSize=[" << dataInfo.objDataInfo->nDataTotalSize << "]"
			<< "EveryPackSize=[" << dataInfo.objDataInfo->nEveryPackSize << "]"
			<< "PackCount=[" << dataInfo.objDataInfo->nPackageCount << "]";
		return false;
	}
	else
	{
		
	}

	return true;
}

bool TaskManager::finishTask( const UserTaskPtr& task )
{
	if (!task)
	{
		return false;
	}

	task->onFinish();

	LOG(INFO)
		<< "\n	Client: [" << task->getUserID()<< "]"
		<< "\n	Task:["	<< task->getTaskID() << "]"
		<< "\n	Finished!!! \n";

	if(_eraseTask(task->getTaskID()))
	{
		return true;
	}
	
	return false;
}

bool TaskManager::_eraseTask( const std::string& taskID )
{
	IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
	MapTasks::iterator itFindTask = _mapAllTasks.find(taskID);
	if (itFindTask != _mapAllTasks.end())
	{
		_mapAllTasks.erase(itFindTask);
		LOG(INFO)
			<< "\n	Erease Task, Remain Task Count:[" << _mapAllTasks.size() <<"] \n";
		return true;
	}
	else
	{
		LOG(WARNING) << "No Task Remove With ID: " << taskID;
	}
	return false;
}

void TaskManager::onClientLossConnection( const std::string& strClientID )
{
	assert(_clientsManager != NULL);
	if (!_clientsManager)
	{
		LOG(ERROR) << "No Clients Manager....";
		return;
	}
	
	MapTasks _tempAllTask;
	{
		IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
		_tempAllTask = _mapAllTasks;
	}

	MapTasks::iterator itTask =
		_tempAllTask.begin();
	while (itTask != _tempAllTask.end())
	{
		if (itTask->second->getUserID() == strClientID)
		{
			itTask = _tempAllTask.erase(itTask);
		}
		else
		{
			itTask++;
		}
	}

	LOG(WARNING)
		<< "\n   Client Lose Connection:" << strClientID
		<< "\n   Remain Task Count:[" << _tempAllTask.size() <<"] \n";

	{
		IceUtil::Monitor< ::IceUtil::Mutex>::Lock lock(*this);
		_mapAllTasks= _tempAllTask;
	}
}

