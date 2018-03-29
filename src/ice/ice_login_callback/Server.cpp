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
#include "ProjectPath.h"
#include "ClientsManager.h"
#include "LoginI.h"
#include "TaskManager.h"
#include <glogInit.h>

using namespace std;

class AsyncServer : public Ice::Application
{
public:
	AsyncServer()
	{
		_ClientsManagerPtr = new ClientsManager();
		_LoginServicePtr = new LoginI(_ClientsManagerPtr);
		_ClientsTaskManagerPtr = new TaskManager(_ClientsManagerPtr);
	}

	virtual int run(int, char*[]);
	virtual void interruptCallback(int);

private:
	Login::LoginServicePtr _LoginServicePtr;
	ClientsManagerPtr _ClientsManagerPtr;
	TaskManagerPtr	_ClientsTaskManagerPtr;
};

int
	main(int argc, char* argv[])
{
	boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
	glog->init(argv[0]);

	AsyncServer app;
	const std::string strConfigFilePath = DirPaths::GetAppRootDataPath() + "\\ice\\ice_fileproc.server";
	return app.main(argc, argv, strConfigFilePath.c_str());
}

int
	AsyncServer::run(int argc, char*[])
{
	if(argc > 1)
	{
		cerr << appName() << ": too many arguments" << endl;
		return EXIT_FAILURE;
	}

	callbackOnInterrupt();
	//////////////////////////////////////////////////////////////////////////
	Ice::CommunicatorPtr _CommunicatorPtr;

	try
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


		Ice::ObjectAdapterPtr adapterLoginService = 
			_CommunicatorPtr->createObjectAdapterWithEndpoints("TestAAA", "default -p 20001");
		adapterLoginService->add(_LoginServicePtr, _CommunicatorPtr->stringToIdentity("112233"));
		adapterLoginService->activate();

		_CommunicatorPtr->waitForShutdown();
	}
	catch(Ice::Exception& e)
	{

	}
	return EXIT_SUCCESS;
}

void
	AsyncServer::interruptCallback(int)
{
	communicator()->shutdown();
}
