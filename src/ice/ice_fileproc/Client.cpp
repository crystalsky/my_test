// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "Login.h"
#include <sstream>
#include <strstream>
#include <iosfwd>
#include "ProjectPath.h"
#include <UUID.h>
#include "LoginCallBackI.h"
#include "DataTransmitter.h"
#include <json.h>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <IceUtil/Thread.h>
#include <IceUtil/Exception.h>
#include <IceUtil/IceUtil.h>
#include <boost/program_options.hpp>
#include "SendDataThread.h"

namespace po = boost::program_options;
#include <boost/progress.hpp>
using namespace std;

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
typedef IceUtil::Handle<MyReporter> MyReporterPtr;

class AsyncClient : public Ice::Application
{
public:
    AsyncClient();

    virtual int run(int, char*[]);

private:
    void exception(const Ice::Exception&);
	
	bool getAdditionFileInfo(const std::string& strFileName,
		DataTransmitter::ArrayData& arrInfoData)
	{
		Json::Value root;
		root["SaveFilePathName"] = strFileName;

		Json::FastWriter writer;
		std::string str = writer.write(root);

		arrInfoData.assign(str.begin(), str.end());

		return !arrInfoData.empty();
// 		Json::Value persons;
// 		{
// 			Json::Value person1;
// 			person1["Name"] = "张三";
// 			person1["Age"] = 15;
// 			person1["Weight"] = 85.5;
// 			persons.append(person1);
// 
// 			Json::Value person2;
// 			person2["Name"] = "李四";
// 			person2["Age"] = 34;
// 			person2["Weight"] = 100.784524;
// 			persons.append(person2);
// 		}
// 		root["Persons"]=persons;

// 		Json::Value arrayString;
// 		{
// 			arrayString.append(Json::Value("11111"));
// 			arrayString.append(Json::Value("22222"));
// 			arrayString.append(Json::Value("33333"));
// 			arrayString.append(Json::Value("44444"));
// 		}
// 		root["ArrayString"] = arrayString;

		

		
	}

	void senddata();
private:
	Login::LoginServicePrx _LoginServicePrx;
	Login::LoginCallBackPtr _loginCallBack;
	DataTransmitter::DataProcPrx _filePxy;
	Ice::Identity _myID;
};

AsyncClient::AsyncClient() :
    Ice::Application(Ice::NoSignalHandling)
{
	_loginCallBack = new LoginCallBackI();

	_myID.name = UtilityKit::generateUUID();
}


// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
	return os;
}

int nTaskNum = 0;
int nTaskSendDataSize = 0;
bool bMutliThread = false;
int nEveryPackSize = 0;
int nSendBufferCount = 0;

int parsercmd(int ac, char* av[])
{
	//std::cout << "argc:" << ac << std::endl;
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "produce help message")
			("tasknum,t", po::value<int>(&nTaskNum)->default_value(1), 
			"Send Data Task Count, must >=1, default is 1")
			("size,s", po::value<int>(&nTaskSendDataSize)->default_value(1),
			"set task data size(MB), must >=1, default is 1")
			("everypacksize,e", po::value<int>(&nEveryPackSize)->default_value(512),
			"set every package size, must >= 100, default = 512")
			("mutithread,m", po::value<int>(), 
			"mutithread option, everty task use one thread")
			("buffernum,b", po::value<int>(&nSendBufferCount)->default_value(10), 
			"send buffer number")
			;

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);  

		if (vm.count("help")) {
			cout << "Usage: options_description [options]\n";
			cout << desc;
			return -1;
		}

		bMutliThread = true;
		if (vm.count("mutithread"))
		{
			bMutliThread = true;
		}             
	}
	catch(std::exception& e)
	{
		cout << e.what() << "\n";
		return -1;
	}    
	return 0;
}

#include <glogInit.h>

int
main(int argc, char* argv[])
{
	boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
	glog->init("ice_fileproc_client");

	AsyncClient app;
	const std::string strConfigFilePath = DirPaths::GetIceConfigPath("ice_fileproc.client");
	return app.main(argc, argv, strConfigFilePath.c_str());
}

char* generateData(int nSize)
{
	char* pNewData = new char[nSize];
	char c = 1;
	for (char *p = pNewData; p != pNewData + nSize;)
	{
		static int i = 0;

		if ((++i % 128) == 0)
		{
			c++;
		}
		*p++ = c;
	}
	return pNewData;
}

void AsyncClient::senddata()
{
	int nThreadCount = 1;
	if (bMutliThread && nTaskNum > 1)
	{
		nThreadCount = nTaskNum;
	}

	const int nSize = nTaskSendDataSize * 1024 * 1024 + rand() % 1024;

	char* pData = generateData(nSize);
	std::list<SendDataThreadPtr> listSendDataThreadPtr;
	std::list<MyReporterPtr> listMyReporterPtr;
	for (int i = 0; i < nThreadCount; ++i)
	{
		SendDataThreadPtr th = new SendDataThread(_filePxy);
		th->setSendData(pData, nSize);
		th->setEveryPackageSize(nEveryPackSize);
		{
			DataTransmitter::TaskInfo tinfo;
			tinfo.strTaskID = IceUtil::generateUUID();
			tinfo.strTaskUser = _myID.name;
			tinfo.taskType = DataTransmitter::TaskTestDataRecv;
			th->setPackBufferCount(nSendBufferCount);

			MyReporterPtr ptr = new MyReporter(th);
			listMyReporterPtr.push_back(ptr);
			th->setTaskInfo(tinfo);
		}
		
		th->startSend();
		listSendDataThreadPtr.push_back(th);
	}

	std::list<SendDataThreadPtr>::iterator iter =
		listSendDataThreadPtr.begin();
	while (iter != listSendDataThreadPtr.end())
	{
		(*iter)->waitforFinished();
		iter++;
	}
}

int
AsyncClient::run(int argc, char* argv[])
{
	if(parsercmd(argc, argv) == -1)
	{
		communicator()->shutdown();
		return -1;
	}

	try
	{
		//TODO can get the properties of the config file...
		Ice::PropertiesPtr pros = 
			communicator()->getProperties();

		//check the LoginService Is Connective....
		_LoginServicePrx = 
			Login::LoginServicePrx::checkedCast(
			communicator()->propertyToProxy("LoginService.Proxy"));

		{//create the adapter for callback connection
			Ice::ObjectAdapterPtr adapterBidConn = 
				communicator()->createObjectAdapter("");

			//Add The Client To bidirection connection
			adapterBidConn->add(_loginCallBack, _myID);
			adapterBidConn->activate();
			_LoginServicePrx->ice_getConnection()->setAdapter(adapterBidConn);
			_LoginServicePrx->loginToService(_myID);
		}
//#define _FILE_SEND
#ifdef _FILE_SEND
		_filePxy = DataTransmitter::DataProcPrx::checkedCast(
			communicator()->propertyToProxy("FileProc.Proxy"));

		if (_filePxy)
		{
			senddata();
		}
#endif
		_LoginServicePrx->loginoff(_myID);	
	}
	catch(const Ice::Exception& ex)
	{
		cerr << ex << endl;
	}

	communicator()->shutdown();
	communicator()->waitForShutdown();

    return EXIT_SUCCESS;
}