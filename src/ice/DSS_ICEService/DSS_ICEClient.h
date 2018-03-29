#ifndef DSS_ICEClient_h__
#define DSS_ICEClient_h__

#include "DSS_ICEService_Export.h"
#include <string>
#include <UtilityKit_HandleClass.h>

class DSS_ICEService_Export DSS_ICEClient
{
	UK_DECLARE_PRIVATE(DSS_ICEClient)
public:
	DSS_ICEClient();
	~DSS_ICEClient();

public:
	bool connect(const std::string ip, int nPort = 20000);

	bool sendTaskDataTransRequest(const std::string& strjsonTrans);

	virtual void onRecvRequstData(const char* data, int nLen){}
protected:
	
private:

};

#endif // DSS_ICEClient_h__
