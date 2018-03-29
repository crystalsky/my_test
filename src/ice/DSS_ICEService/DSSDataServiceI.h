#ifndef LoginI_h__
#define LoginI_h__

#include "DSSDataService.h"
#include "ClientsManager.h"
#include "TaskManager.h"

class DSSDataServiceI : virtual public DSSDataService::DSSService
{
public:

    DSSDataServiceI(const ClientsManagerPtr& manager);

    virtual bool loginOn(const ::DSSDataService::DSSServiceCallBackPrx&, const ::Ice::Current& = ::Ice::Current());
	virtual bool loginOff(const ::DSSDataService::DSSServiceCallBackPrx&, const ::Ice::Current& = ::Ice::Current());

	virtual ::TaskDataDef::emRequestResultType requestData(const ::TaskDataDef::TaskRequestPtr&, const ::Ice::Current& = ::Ice::Current());
private:
	ClientsManagerPtr m_ClientsManagerPtr;
	TaskManagerPtr	m_TaskManagerPtr;
};


#endif // LoginI_h__
