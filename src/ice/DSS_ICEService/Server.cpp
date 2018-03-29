// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "ProjectPath.h"
#include "ClientsManager.h"
#include "DSSDataServiceI.h"
#include "TaskManager.h"
#include <glogInit.h>

using namespace std;

class AsyncServer
{
public:
	AsyncServer()
	{
		char** argv = new char*[1];
		argv[0] = new char[200];
		strcpy(argv[0] , "--Ice.MessageSizeMax=10240000");
		int argc = 1;
		if(_CommunicatorPtr == NULL)
			_CommunicatorPtr = Ice::initialize(argc, argv);
		assert(_CommunicatorPtr != NULL);

		delete[] argv[0];
		delete[] argv;

		//////////////////////////////////////////////////////////////////////////
		_ClientsManagerPtr = new ClientsManager();
		_LoginServicePtr = new DSSDataServiceI(_ClientsManagerPtr);
		_ClientsTaskManagerPtr = new TaskManager(_ClientsManagerPtr);
	}

    bool startServer()
	{
		if (!_CommunicatorPtr)
		{
			return false;
		}
		
		try
		{
			const std::string str1 = "tcp -h localhost -p 20000";
			const std::string str2 = "default -p 20000";
			Ice::ObjectAdapterPtr adapterLoginService = 
				_CommunicatorPtr->createObjectAdapterWithEndpoints("DSSService", str2);
			adapterLoginService->add(_LoginServicePtr, _CommunicatorPtr->stringToIdentity("login"));
			adapterLoginService->activate();

			_CommunicatorPtr->waitForShutdown();
		}
		catch(Ice::Exception& e)
		{
			LOG(ERROR) << e.what();
		}
		
		return true;
	}

private:
	DSSDataService::DSSServicePtr _LoginServicePtr;
	ClientsManagerPtr _ClientsManagerPtr;
	TaskManagerPtr	_ClientsTaskManagerPtr;

	Ice::CommunicatorPtr _CommunicatorPtr;
};

int
main(int argc, char* argv[])
{
	boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
	glog->init(argv[0]);

    AsyncServer app;
	app.startServer();
	return 0;
}

