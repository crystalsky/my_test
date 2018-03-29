#ifndef TaskManager_h__
#define TaskManager_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "UserTask.h"
#include "DSSDataService.h"
#include <IceUtil/IceUtil.h>
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

class ClientsManager;
//class TaskDataQueue;
class TaskManager : public IceUtil::Shared,
	public ::IceUtil::Monitor< ::IceUtil::Mutex>
{
	//friend class TaskDataQueue;
public:
	TaskManager(const IceUtil::Handle<ClientsManager>& ptrClientsManager);
	~TaskManager();

public:
	::TaskDataDef::emRequestResultType requestData(
		const ::TaskDataDef::TaskRequestPtr& data);
protected:
	virtual TaskPtr createTask(
		const ::DSSDataService::DSSServiceCallBackPrx& pxyClient,
		const ::TaskDataDef::TaskRequestPtr& data);

	void onClientLossConnection(const std::string& strClientID);

	TaskPtr getTaskByTaskID(const std::string& strTaskID);

	bool finishTask(const TaskPtr& task);

	bool _eraseTask(const std::string& taskID);
private:
	IceUtil::Handle<ClientsManager> m_clientsManager;
	MapTasks	_mapAllTasks;
	//IceUtil::Handle<TaskDataQueue> _taskDataQueue;

	bs2::connection	_connection;
};
typedef IceUtil::Handle<TaskManager> TaskManagerPtr;


#endif // TaskManager_h__
