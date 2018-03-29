#include "DSSServiceCallBackI.h"


DSSServiceCallBackI::DSSServiceCallBackI(const Ice::Identity& _ID)
										 : _myID(_ID)
										 , m_pClientProc(NULL)
{
	
}

DSSServiceCallBackI::DSSServiceCallBackI(DSS_ICEClient* pProc,
										 const Ice::Identity& _ID)
										 : _myID(_ID)
										 , m_pClientProc(pProc)
{
	assert(m_pClientProc != NULL);
}

DSSServiceCallBackI::~DSSServiceCallBackI()
{

}

::std::string DSSServiceCallBackI::getName( const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	return _myID.name;
}

void DSSServiceCallBackI::setReuestResult( const ::DSSDataService::TaskResultDataPtr&, const ::Ice::Current& /*= ::Ice::Current()*/ )
{

}
