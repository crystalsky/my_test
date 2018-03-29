#ifndef DataTransmitterI_h__
#define DataTransmitterI_h__

#include "DataTransmitter.h"
#include "TaskManager.h"

class DataProcI : virtual public DataTransmitter::DataProc
{
public:
    DataProcI(const TaskManagerPtr&);
	
	virtual bool ice_isA(const ::std::string& s, const ::Ice::Current& cur= ::Ice::Current()) const;
	virtual void setReadySendDataInfo(const ::DataTransmitter::SendDataInfo&, const ::Ice::Current& = ::Ice::Current());
    virtual void sendData(const ::DataTransmitter::SendDataPackagePtr&, const ::Ice::Current& = ::Ice::Current());
    virtual bool checkTaskDataInfo(const ::DataTransmitter::CheckDataInfo&, const ::Ice::Current& = ::Ice::Current());
	virtual void shutdown(const Ice::Current&);

private:

    TaskManagerPtr _TaskMgrPtr;
};


#endif // DataTransmitterI_h__
