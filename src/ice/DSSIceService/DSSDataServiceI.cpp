// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "DSSDataServiceI.h"
//#include "ClientsManager.h"
#include <glog.h>

using namespace std;

DSSDataServiceI::DSSDataServiceI(/*const ClientsManagerPtr& workQueue*/)// :
    //m_ClientsManagerPtr(workQueue)
{

}

bool DSSDataServiceI::loginOn( const ::DSSDataService::DSSServiceCallBackPrx &pxy, const ::Ice::Current& cur )
{
	//m_ClientsManagerPtr->addClientPrx(pxy->ice_getIdentity(), pxy);
	//test
	//std::string strName = clientCallBack->getName();

	//TODO ����ͨ���ص�����ķ�����ȡ�ͻ�����Ϣ������������δ����ԭ��
	//TODO 1.�������Timer����߳���Ͳ��������������ǵ��ô˺������߳��������⵼�£������ڻص��������²��ܵ��ûص������ķ���
	//std::string strClientName = clientCallBack->getName();

	//clientCallBack->setServerName("MyLoginServer");

	//std::cout << "User " << id.name << " Login To Server..";

	return true;
}

bool DSSDataServiceI::loginOff( const ::DSSDataService::DSSServiceCallBackPrx &pxy, const ::Ice::Current& cur )
{
	//m_ClientsManagerPtr->removeClientPrx(id);
	return true;
}

bool DSSDataServiceI::requestData( const ::Ice::Identity&, const ::DSSDataService::TaskRequestPtr&, const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	return true;
}

