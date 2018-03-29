#include "DSS_ICEClient.h"
#include <Ice/Ice.h>
#include <sstream>
#include <strstream>
#include <iosfwd>
#include <UUID.h>
#include <glog.h>
#include "DSSServiceCallBackI.h"
#include <json.h>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <IceUtil/Thread.h>
#include <IceUtil/Exception.h>
#include <IceUtil/IceUtil.h>
#include <CRCUtil.h>
#include <boost/program_options.hpp>
#include <sstream>
#include <boost/format.hpp>
#include "CRCUtil.h"

class DSS_ICEClientPrivate
{
	UK_DECLARE_PUBLIC(DSS_ICEClient);
public:
	DSS_ICEClientPrivate()
		: m_strServiceName("DSS_ICE_SERVICE")
		, m_strClientID(UtilityKit::generateUUID())
	{
		init();
	}

	~DSS_ICEClientPrivate()
	{
		if (_DSSServicePrx && _DSSServiceCallBackPrx)
		{
			_DSSServicePrx->loginOff(_DSSServiceCallBackPrx);
		}
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

			return true;

		}
		catch(const Ice::Exception& ex)
		{
			LOG(ERROR) << "Init ICE Failed.." << ex.what();
		}
		return false;
	}

	bool connect(const std::string ip, int nPort)
	{
		if (!_CommunicatorPtr)
		{
			return false;
		}

		try
		{
			//login:tcp -h localhost -p 20000
			//boost::format fmt("%1%:tcp -h %2% -p %3%");
			//fmt % m_strServiceName % ip % nPort;
			boost::format fmt("%1%:default -p %2%");
			fmt % m_strServiceName % nPort;
			const std::string strServer = fmt.str();

			_DSSServicePrx = 
				DSSDataService::DSSServicePrx::checkedCast(
				_CommunicatorPtr->stringToProxy(strServer)->ice_twoway()->ice_timeout(-1)->ice_secure(false));

			Ice::ObjectAdapterPtr adapter = _CommunicatorPtr->createObjectAdapterWithEndpoints("", "default -h localhost");
			DSSDataService::DSSServiceCallBackPtr cr = new DSSServiceCallBackI;
			adapter->add(cr, _CommunicatorPtr->stringToIdentity(m_strClientID));
			adapter->activate();

			_DSSServiceCallBackPrx = DSSDataService::DSSServiceCallBackPrx::uncheckedCast(
				adapter->createProxy(_CommunicatorPtr->stringToIdentity(m_strClientID)));

			if(_DSSServicePrx->loginOn(_DSSServiceCallBackPrx))
			{
				return true;
			}
		}
		catch(const Ice::ObjectAdapterDeactivatedException& ex)
		{
			LOG(ERROR) << "Ice::ObjectAdapterDeactivatedException.." << ex.name;
		}
		catch(const Ice::Exception& ex)
		{
			LOG(ERROR) << "Init ICE Failed.." << ex.what();
		}
		
		return false;
	}

	bool sendTaskDataTransRequest(const std::string& strjsonTrans)
	{
		TaskDataDef::ArrayData data(strjsonTrans.begin(), strjsonTrans.end());

		unsigned long nDataCRC = 
			UtilityKit::crc32_UseStaticTable((const char*)&data[0], 
			data.size());

		Ice::Identity _myID = _DSSServiceCallBackPrx->ice_getIdentity();

		TaskDataDef::TaskRequestPtr requestInfo(new TaskDataDef::TaskRequest(
			TaskDataDef::TaskDataTrans,
			UtilityKit::generateUUID(),
			_myID,
			data, 
			nDataCRC));

		return _DSSServicePrx->requestData(requestInfo);
	}

	DSSDataService::DSSServicePrx _DSSServicePrx;
	DSSDataService::DSSServiceCallBackPrx _DSSServiceCallBackPrx;
	Ice::CommunicatorPtr _CommunicatorPtr;

	const std::string m_strClientID;
	const std::string m_strServiceName;
};

DSS_ICEClient::DSS_ICEClient()
{
	UK_INIT_PRIVATE(DSS_ICEClient);

	UK_D(DSS_ICEClient);
	if(!d.init())
	{
		assert(false);
	}
}

DSS_ICEClient::~DSS_ICEClient()
{
	UK_FINI_PRIVATE();
}

bool DSS_ICEClient::connect( const std::string ip, int nPort )
{
	UK_D(DSS_ICEClient);
	if (d.connect(ip, nPort))
	{
		return true;
	}
	return false;
}

bool DSS_ICEClient::sendTaskDataTransRequest( const std::string& strjsonTrans )
{
	UK_D(DSS_ICEClient);

	return d.sendTaskDataTransRequest(strjsonTrans);
}
