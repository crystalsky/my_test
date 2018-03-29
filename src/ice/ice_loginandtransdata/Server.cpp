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

class AsyncServer : public Ice::Application
{
public:
	AsyncServer()
	{
		_ClientsManagerPtr = new ClientsManager();
		_LoginServicePtr = new DSSDataServiceI(_ClientsManagerPtr);
		_ClientsTaskManagerPtr = new TaskManager(_ClientsManagerPtr);
	}

	virtual int run(int argc, char* argv[])
	{
		try
		{
			const std::string str1 = "tcp -h 192.168.0.36 -p 20000";
			const std::string str2 = "default -p 20000";

			Ice::ObjectAdapterPtr adapter =
				communicator()->createObjectAdapterWithEndpoints("DSS_ICE_SERVICE", str2);

			adapter->add(_LoginServicePtr, communicator()->stringToIdentity("DSS_ICE_SERVICE"));
			adapter->activate();

			communicator()->waitForShutdown();
		}
		catch(Ice::Exception& e)
		{
			LOG(ERROR) << e.what();
		}

		return 0;
	}

	virtual void interruptCallback(int)
	{

	}

private:
	DSSDataService::DSSServicePtr _LoginServicePtr;
	ClientsManagerPtr _ClientsManagerPtr;
	TaskManagerPtr	_ClientsTaskManagerPtr;
};

#include "DSS_ICEServiceServer.h"
int
main(int argc, char* argv[])
{
	/*boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
	glog->init(argv[0]);
	
	char** argvIce = new char*[1];
	argvIce[0] = new char[200];
	strcpy(argv[0] , "--Ice.MessageSizeMax=10240000");
	argc = 1;

    AsyncServer app;
	return app.main(argc, argvIce);*/

	DSS_ICEServiceServer server;
	server.startService(20000);

	return -1;
}

