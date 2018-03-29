#include "DSS_ICEServiceServer.h"
#include <Ice/Ice.h>
#include "ClientsManager.h"
#include "DSSDataServiceI.h"
#include "TaskManager.h"
#include <glog.h>
#include <boost/program_options.hpp>
#include <sstream>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/format.hpp>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time.hpp>

class ServerApp : public IceUtil::Shared
{
public:
	ServerApp()
		: m_strServiceName("DSS_ICE_SERVICE")
	{
		_ClientsManagerPtr = new ClientsManager();
		_LoginServicePtr = new DSSDataServiceI(_ClientsManagerPtr);
		
	}

	bool init()
	{
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

			return _CommunicatorPtr != NULL;

		}
		catch(const Ice::Exception& ex)
		{
			LOG(ERROR) << "Init ICE Failed.." << ex.what();
		}
		return false;
	}

	bool startServer(int nPort)
	{
		if(!init())
		{
			return false;
		}

		try
		{
			//const std::string str1 = "tcp -h 192.168.0.36 -p 20000";
			boost::format fmt("default -p %1%");
			fmt % nPort;
			const std::string strServer = fmt.str();

			Ice::ObjectAdapterPtr adapter =
				_CommunicatorPtr->createObjectAdapterWithEndpoints(m_strServiceName, strServer);

			adapter->add(_LoginServicePtr, _CommunicatorPtr->stringToIdentity(m_strServiceName));
			adapter->activate();
		
			_CommunicatorPtr->waitForShutdown();
		}
		catch(Ice::Exception& e)
		{
			LOG(ERROR) << e.what();
			return false;
		}

		return true;
	}

	bool stopService()
	{
		if (_CommunicatorPtr)
		{
			_CommunicatorPtr->shutdown();
		}
		return true;
	}
private:
	DSSDataService::DSSServicePtr _LoginServicePtr;
	ClientsManagerPtr _ClientsManagerPtr;
	Ice::CommunicatorPtr _CommunicatorPtr;

	const std::string m_strServiceName;
};

class DSS_ICEServiceServerPrivate : public IceUtil::Thread
{
	UK_DECLARE_PUBLIC(DSS_ICEServiceServer);
public:
	DSS_ICEServiceServerPrivate()
		: m_ServerApp(new ServerApp)
		, m_nStartStatus(0)
		, m_semaphore(0)
	{

	}

	virtual void run()
	{
		
	}

	bool startService(int nPort)
	{
		m_nPort = nPort;

		m_nStartStatus = true;
		m_nStartStatus = m_ServerApp->startServer(m_nPort);

		//start();

		//m_semaphore.post();

		//using namespace boost::posix_time;
		//ptime pt = second_clock::universal_time() + seconds(2);
		//m_semaphore.timed_wait(pt);

		return m_nStartStatus;
	}

	bool stopService()
	{
		m_ServerApp->stopService();
		
		return false;
	}

	IceUtil::Handle<ServerApp> m_ServerApp;
	bool m_nStartStatus;
	int m_nPort;

	boost::interprocess::interprocess_semaphore m_semaphore;
};

DSS_ICEServiceServer::DSS_ICEServiceServer()
{
	UK_INIT_PRIVATE(DSS_ICEServiceServer);
}

DSS_ICEServiceServer::~DSS_ICEServiceServer()
{
	UK_FINI_PRIVATE();
}

bool DSS_ICEServiceServer::startService( int nPort /*= 20000*/ )
{
	UK_D(DSS_ICEServiceServer);
	if (d.startService(nPort))
	{
		return true;
	}
	return false;
}

bool DSS_ICEServiceServer::stopService()
{
	UK_D(DSS_ICEServiceServer);
	if (d.stopService())
	{
		return true;
	}
	return false;
}

