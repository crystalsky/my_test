#include "TaskManager.h"
#include <glog.h>
#include "ClientsManager.h"
#include <boost/bind.hpp>
#include <CRCUtil.h>
#include "TaskDataTrans.h"

TaskManager::TaskManager(const IceUtil::Handle<ClientsManager>& ptrClientsManager)
	: m_clientsManager(ptrClientsManager)
{
	assert(m_clientsManager != NULL);

	//_taskDataQueue = new TaskDataQueue(this);
	//_taskDataQueue->start();

	if (m_clientsManager)
	{
		_connection = m_clientsManager->connectOnLoseConnection(
			boost::bind(&TaskManager::onClientLossConnection, this, _1));
	}
}

TaskManager::~TaskManager()
{
	_connection.disconnect();
	//_taskDataQueue->destroy();
}

::TaskDataDef::emRequestResultType TaskManager::requestData(const ::TaskDataDef::TaskRequestPtr& data )
{
	//create the task
	DSSDataService::DSSServiceCallBackPrx pxyClient = 
		m_clientsManager->FindClientByID(data->userID.name);
	
	if (!pxyClient)
	{
		LOG(ERROR) << "No Client Pxy....";
		return ::TaskDataDef::RTInvalideClientID;
	}
	
	TaskPtr taskPtr = createTask(pxyClient, data);
	if (!taskPtr)
	{
		LOG(ERROR) << "CreateTask Failed....";
		return ::TaskDataDef::RTCreateTaskFaild;
	}
	

	return ::TaskDataDef::RTNoError;
}

TaskPtr TaskManager::getTaskByTaskID( const std::string& strTaskID )
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
	return TaskPtr();
}

bool TaskManager::finishTask( const TaskPtr& task )
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

TaskPtr TaskManager::createTask(const ::DSSDataService::DSSServiceCallBackPrx& pxyClient,	
									const ::TaskDataDef::TaskRequestPtr& data )
{
	TaskPtr ptrTask;
	switch (data->TaskType)
	{
	case TaskDataDef::TaskFileTransfer:
		{
			//ptrTask.reset(new FileTransferTask(pxyClient));
		}
		break;
	case TaskDataDef::TaskTestDataRecv:
	case TaskDataDef::TaskCaculate:
	case TaskDataDef::TaskOther:
		{
			ptrTask.reset(new UserTask(pxyClient));
		}
		break;
	case TaskDataDef::TaskDataTrans:
		{
			ptrTask.reset(new TaskDataTrans(pxyClient));
		}
	default:
		{
			LOG(WARNING) << "No Support TaskType...";
		}
		break;
	}

	if (ptrTask)
	{
		if(!ptrTask->initTaskInfo(data))
		{
			LOG(ERROR) << "Initial Task Failed....";
			ptrTask.swap(TaskPtr());
		}
		else
		{
			LOG(INFO) << "TaskCreated...! "
				//<< "\n	Client: [" << data->strTaskUser << "]"
				<< "\n	TaskCr:["	<< data->strTaskID << "]";
			//<< "\n	DataSize=[" << data->nDataTotalSize << "]"
			//<< "\n	EveryPackSize=[" << data->nEveryPackSize << "]"
			//<< "\n	PackCount=[" << data->nPackageCount << std::endl;
		}
	}

	return ptrTask;
}

void TaskManager::onClientLossConnection( const std::string& strClientID )
{
	assert(m_clientsManager != NULL);
	if (!m_clientsManager)
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
		_mapAllTasks = _tempAllTask;
	}
}

