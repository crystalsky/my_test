// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <sstream>
#include <strstream>
#include <iosfwd>
#include "ProjectPath.h"
#include <UUID.h>
#include "DSSServiceCallBackI.h"
#include <json.h>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <IceUtil/Thread.h>
#include <IceUtil/Exception.h>
#include <IceUtil/IceUtil.h>
#include <boost/program_options.hpp>
#include <sstream>
#include <boost/format.hpp>

namespace po = boost::program_options;
#include <boost/progress.hpp>
#include "../ice_fileproc/CRCUtil.h"
using namespace std;
/*
class MyReporter : public IceUtil::Shared
{
	bs2::connection _con;
public:
	MyReporter(const SendDataThreadPtr& ptr)
	{
		_SendDataThread = ptr;
		_con = _SendDataThread->connectProgressReport(
			boost::bind(&MyReporter::setProgress, this, _1, _2));
	}

	virtual void setProgress(int nTotal, int nSended)
	{
		if (!_progress)
		{
			_progress.reset(new boost::progress_display(nTotal));
		}
		(*_progress) += nSended;
	}

private:
	SendDataThreadPtr _SendDataThread;
	boost::shared_ptr<boost::progress_display> _progress;
};
typedef IceUtil::Handle<MyReporter> MyReporterPtr;*/
class DSSClientProc
{
public:
	DSSClientProc()
		: m_strServiceName("DSS_ICE_SERVICE")
	{
		_myID.name = UtilityKit::generateUUID();

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
		}
		catch(const Ice::Exception& ex)
		{
			cerr << ex << endl;
		}
	}

	~DSSClientProc()
	{
		if (_DSSServicePrx)
		{
			_DSSServicePrx->loginOff(_myID);
		}
		_CommunicatorPtr->shutdown();
		_CommunicatorPtr->waitForShutdown();
	}

	bool init(const std::string ip, int nPort)
	{
		if (!_CommunicatorPtr ||
			!m_pClientProc)
		{
			return false;
		}

		_CommunicatorPtr->shutdown();

		try
		{
			boost::format fmt("%1%:tcp -h %2% -p %3%");
			fmt % m_strServiceName % ip % nPort;
			const std::string strServer = fmt.str();
			
			 _DSSServicePrx =
				DSSDataService::DSSServicePrx::checkedCast(
				_CommunicatorPtr->stringToProxy(strServer));

			//create the adapter for callback connection
			Ice::ObjectAdapterPtr adapterBidConn = 
				_CommunicatorPtr->createObjectAdapter("");

			_DSSServiceCallBackPrx = new DSSServiceCallBackI(_myID);
			//Add The Client To bidirection connection
			adapterBidConn->add(_DSSServiceCallBackPrx, _myID);
			adapterBidConn->activate();

			_DSSServicePrx->ice_getConnection()->setAdapter(adapterBidConn);

			if(_DSSServicePrx->loginOn(_myID))
			{
				return true;
			}
			return true;
		}
		catch(const Ice::Exception& ex)
		{
			cerr << ex << endl;
		}
		return false;
	}

	bool sendTaskDataTransRequest(const std::string& strjsonTrans)
	{
		DSSDataService::ArrayData data(strjsonTrans.begin(), strjsonTrans.end());

		unsigned long nDataCRC = 
			CRCUtil::crc32_UseStaticTable((const char*)&data[0], 
			data.size());

		DSSDataService::TaskRequestPtr requestInfo(new DSSDataService::TaskRequest(
			DSSDataService::TaskDataTrans,
			UtilityKit::generateUUID(),
			_myID.name,
			data, 
			nDataCRC));

		return _DSSServicePrx->requestData(_myID, requestInfo);
	}

	virtual void onRecvRequstData(const char* data, int nLen)
	{

	}
private:
	DSSDataService::DSSServicePrx _DSSServicePrx;
	DSSDataService::DSSServiceCallBackPtr _DSSServiceCallBackPrx;

	Ice::CommunicatorPtr _CommunicatorPtr;

	Ice::Identity _myID;

	const std::string m_strServiceName;
};


#include <glogInit.h>

int
	main(int argc, char* argv[])
{
	boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
	glog->init("ice_fileproc_client");

	AsyncClient app;
	app.init();


	return 0;
}
