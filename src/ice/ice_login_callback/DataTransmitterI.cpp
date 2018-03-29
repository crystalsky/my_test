// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "DataTransmitterI.h"

using namespace std;

DataProcI::DataProcI(const TaskManagerPtr& taskMgr) :
    _TaskMgrPtr(taskMgr)
{
}

void DataProcI::sendData(const ::DataTransmitter::SendDataPackagePtr& data, const ::Ice::Current&)
{
	if (_TaskMgrPtr)
	{
		_TaskMgrPtr->setRecvDataPackage(/*cb, */data);
	}
}

bool DataProcI::checkTaskDataInfo( const ::DataTransmitter::CheckDataInfo& cdInfo, const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	if (_TaskMgrPtr)
	{
		return _TaskMgrPtr->checkTaskDataInfo(cdInfo);
	}
	return false;
}

void DataProcI::setReadySendDataInfo(const ::DataTransmitter::SendDataInfo& sendDataInfo, const ::Ice::Current&)
{
	if (_TaskMgrPtr)
	{
		_TaskMgrPtr->processUserDataInfo(sendDataInfo);
	}
}

void
DataProcI::shutdown(const Ice::Current& curr)
{
    cout << "Shutting down..." << endl;

    //curr.adapter->getCommunicator()->shutdown();
}

bool DataProcI::ice_isA( const ::std::string& s, const ::Ice::Current& cur/*= ::Ice::Current()*/ ) const
{
	if (DataProc::ice_isA(s, cur))
	{
// 		::Ice::EndpointSeq vseq = cur.adapter->getEndpoints();
// 		if (!vseq.empty())
// 		{
// 			std::cout << vseq[0]->toString() << std::endl;
// 		}
// 
// 		::Ice::EndpointSeq vseq1 = cur.adapter->getPublishedEndpoints();
// 		std::string str = cur.adapter->getName();
// 		std::cout << "=====FileProcCon: " 
// 			<< "==Current.Connection.String:" << cur.con->toString() 
// 			<< "==Current.Adapter.Name:" << cur.adapter->getName()
// 			<< "==Current.ID:" << cur.id.name
// 			<< "==" << 
// 			std::endl;

		return true;
	}

	return false;
}
