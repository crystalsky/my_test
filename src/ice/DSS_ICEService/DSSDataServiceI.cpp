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
#include "CRCUtil.h"

using namespace std;

DSSDataServiceI::DSSDataServiceI(const ClientsManagerPtr& manager)
	: m_ClientsManagerPtr(manager)
	, m_TaskManagerPtr(new TaskManager(manager))
{
	

}

bool DSSDataServiceI::loginOn( const ::DSSDataService::DSSServiceCallBackPrx &pxy, const ::Ice::Current& cur )
{
	m_ClientsManagerPtr->addClientPrx(pxy->ice_getIdentity(), pxy);
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
	m_ClientsManagerPtr->removeClientPrx(pxy->ice_getIdentity());

	return true;
}

::TaskDataDef::emRequestResultType DSSDataServiceI::requestData( 
	const ::TaskDataDef::TaskRequestPtr& data, 
	const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	//check the data crc....
	unsigned long ndataCrc = UtilityKit::crc32_UseStaticTable(
		(const char*)&data->arrAddtionalData[0], data->arrAddtionalData.size());

	if (ndataCrc != data->nAddtionalDataCRC)
	{
		LOG(ERROR) << "Invalide request data, CRC Not Equaled";
		return ::TaskDataDef::RTAdditionalDataCRCFailed;
	}

	::TaskDataDef::emRequestResultType emResult = 
		m_TaskManagerPtr->requestData(data);

	return emResult;
}

