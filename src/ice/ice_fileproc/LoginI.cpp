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

		//TODO 这里通过回调对象的方法获取客户端信息，会阻塞，还未查明原因？
		//TODO 1.在另外的Timer里或线程里就不会阻塞，估计是调用此函数的线程死锁问题导致，所以在回调的条件下不能调用回调函数的方法
		//std::string strClientName = clientCallBack->getName();

		//clientCallBack->setServerName("MyLoginServer");

		//std::cout << "User " << id.name << " Login To Server..";
	}
}

void LoginI::loginoff( const ::Ice::Identity& id, const ::Ice::Current& cur )
{
	m_ClientsManagerPtr->removeClientPrx(id);
}

