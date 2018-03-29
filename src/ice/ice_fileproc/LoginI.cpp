// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "LoginI.h"
#include "ClientsManager.h"
#include <glog.h>

using namespace std;

LoginI::LoginI(const ClientsManagerPtr& workQueue) :
    m_ClientsManagerPtr(workQueue)
{

}

void LoginI::loginToService( const ::Ice::Identity& id, const ::Ice::Current& cur )
{
	Login::LoginCallBackPrx clientCallBack =
		Login::LoginCallBackPrx::uncheckedCast(cur.con->createProxy(id));

	if (clientCallBack)
	{
		m_ClientsManagerPtr->addClientPrx(id, clientCallBack);
		//test
		//std::string strName = clientCallBack->getName();

		//TODO ����ͨ���ص�����ķ�����ȡ�ͻ�����Ϣ������������δ����ԭ��
		//TODO 1.�������Timer����߳���Ͳ��������������ǵ��ô˺������߳��������⵼�£������ڻص��������²��ܵ��ûص������ķ���
		//std::string strClientName = clientCallBack->getName();

		//clientCallBack->setServerName("MyLoginServer");

		//std::cout << "User " << id.name << " Login To Server..";
	}
}

void LoginI::loginoff( const ::Ice::Identity& id, const ::Ice::Current& cur )
{
	m_ClientsManagerPtr->removeClientPrx(id);
}

