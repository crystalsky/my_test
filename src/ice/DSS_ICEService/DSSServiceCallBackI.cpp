#include "DSSServiceCallBackI.h"

DSSServiceCallBackI::DSSServiceCallBackI(//DSS_ICEClient* pProc,
										 /*const Ice::Identity& _ID*/)
	//: _myID(_ID)
	//, m_pClientProc(pProc)
{
	//assert(m_pClientProc != NULL);
}

DSSServiceCallBackI::~DSSServiceCallBackI()
{
	
}

::std::string DSSServiceCallBackI::getName( const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	return _myID.name;
}

void DSSServiceCallBackI::setReuestResult( const ::TaskDataDef::TaskResultDataPtr&, const ::Ice::Current& /*= ::Ice::Current()*/ )
{

}
