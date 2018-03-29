#ifndef DSSServiceCallBackI_h__
#define DSSServiceCallBackI_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "DSSDataService.h"

class DSS_ICEClient;
class DSSServiceCallBackI : public DSSDataService::DSSServiceCallBack
{
public:
	DSSServiceCallBackI(
		//DSS_ICEClient* pProc,
		//const Ice::Identity& _ID
		);
	~DSSServiceCallBackI();

public:
	virtual ::std::string getName(const ::Ice::Current& = ::Ice::Current());

	virtual void setReuestResult(const ::TaskDataDef::TaskResultDataPtr&, const ::Ice::Current& = ::Ice::Current());
protected:
	
private:
	DSS_ICEClient*	m_pClientProc;
	Ice::Identity _myID;
};

#endif // DSSServiceCallBackI_h__
