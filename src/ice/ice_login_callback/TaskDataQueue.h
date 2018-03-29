#ifndef TaskDataQueue_h__
#define TaskDataQueue_h__

#include <list>
#include "DataTransmitter.h"
#include <IceUtil/IceUtil.h>

class TaskManager;
class TaskDataQueue : public IceUtil::Thread
{
public:
	TaskDataQueue(const IceUtil::Handle<TaskManager>& mng);

	virtual void run();

	void addRecvData(/*const DataTransmitter::AMD_DataProc_sendDataPtr&, */
		const DataTransmitter::SendDataPackagePtr& fileData);
	void destroy();
private:
	struct CallbackEntry
	{
		//DataTransmitter::AMD_DataProc_sendDataPtr cb;
		DataTransmitter::SendDataPackagePtr data;
	};

	IceUtil::Handle<TaskManager>	_TaskManagerPtr;

	IceUtil::Monitor<IceUtil::Mutex> _monitor;
	std::list<CallbackEntry> _queueTaskDatas;
	bool _done;
};
typedef IceUtil::Handle<TaskDataQueue> FileInfoQueuePtr;

#endif // TaskDataQueue_h__
