#ifndef TaskManager_h__
#define TaskManager_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "UserTask.h"
#include "DataTransmitter.h"
#include <IceUtil/IceUtil.h>
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

class ClientsManager;
class TaskDataQueue;
class TaskManager : public IceUtil::Shared,
	public ::IceUtil::Monitor< ::IceUtil::Mutex>
{
	friend class TaskDataQueue;
public:
	TaskManager(const IceUtil::Handle<ClientsManager>& ptrClientsManager);
	~TaskManager();

public:
	bool processUserDataInfo(const ::DataTransmitter::SendDataInfo& dataInfo);
	void setRecvDataPackage(
		/*const ::DataTransmitter::AMD_DataProc_sendDataPtr& cb, */
		const ::DataTransmitter::SendDataPackagePtr& data);
	bool checkTaskDataInfo(const ::DataTransmitter::CheckDataInfo& cdInfo);
protected:
	void onClientLossConnection(const std::string& strClientID);

	UserTaskPtr getTaskByTaskID(const std::string& strTaskID);
	UserTaskPtr createTask(
		const Login::LoginCallBackPrx& clientPtr,
		const ::DataTransmitter::SendDataInfo& dataInfo);
	bool checkSendDataInfo(const DataTransmitter::SendDataInfo& dataInfo)const;
	bool finishTask(const UserTaskPtr& task);

	bool _eraseTask(const std::string& taskID);
private:
	IceUtil::Handle<ClientsManager> _clientsManager;
	MapTasks	_mapAllTasks;
	IceUtil::Handle<TaskDataQueue> _taskDataQueue;

	bs2::connection	_connection;
};
typedef IceUtil::Handle<TaskManager> TaskManagerPtr;


#endif // TaskManager_h__
