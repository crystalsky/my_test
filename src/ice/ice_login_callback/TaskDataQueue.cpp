// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "TaskDataQueue.h"
#include "TaskManager.h"

using namespace std;
//////////////////////////////////////////////////////////////////////////
TaskDataQueue::TaskDataQueue(const IceUtil::Handle<TaskManager>& mng)
	: _done(false)
	, _TaskManagerPtr(mng)
{

}

void
	TaskDataQueue::run()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

	while(!_done)
	{
		if(_queueTaskDatas.size() == 0)
		{
			_monitor.wait();
		}

		if(_queueTaskDatas.size() != 0)
		{
			CallbackEntry entry = _queueTaskDatas.front();
			bool bProcData = false;
			if (_TaskManagerPtr)
			{
				UserTaskPtr ptrTask = _TaskManagerPtr->getTaskByTaskID(entry.data->strTaskID);

				if(ptrTask)
				{
					ptrTask->onRecvData(entry.data);
					bProcData = true;
				}

				//entry.cb->ice_response();
			}

			if (bProcData)
			{
				_queueTaskDatas.pop_front();
			}
		}
	}

	//
	// Throw exception for any outstanding requests.
	//
// 	list<CallbackEntry>::const_iterator p;
// 	for(p = _queueTaskDatas.begin(); p != _queueTaskDatas.end(); ++p)
// 	{
// 		(*p).cb->ice_exception(DataTransmitter::RequestCanceledException());
// 	}
}

void 
	TaskDataQueue::addRecvData(/*const DataTransmitter::AMD_DataProc_sendDataPtr& cb, */
	const DataTransmitter::SendDataPackagePtr& fileData)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

	if(!_done)
	{
		//
		// Add work item.
		//
		CallbackEntry entry;
		//entry.cb = cb;
		entry.data = fileData;

		if(_queueTaskDatas.size() == 0)
		{
			_monitor.notify();
		}
		_queueTaskDatas.push_back(entry);
	}
	else
	{
		//
		// Destroyed, throw exception.
		//
		//cb->ice_exception(DataTransmitter::RequestCanceledException());
	}
}

void
	TaskDataQueue::destroy()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

	//
	// Set done flag and notify.
	//
	_done = true;
	_monitor.notify();
}
