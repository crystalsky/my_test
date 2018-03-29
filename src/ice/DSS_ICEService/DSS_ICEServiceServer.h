#ifndef DSS_ICEServiceServer_h__
#define DSS_ICEServiceServer_h__

#include "DSS_ICEService_Export.h"
#include <string>
#include <UtilityKit_HandleClass.h>

class DSS_ICEService_Export DSS_ICEServiceServer
{
	UK_DECLARE_PRIVATE(DSS_ICEServiceServer)
public:
	DSS_ICEServiceServer();
	~DSS_ICEServiceServer();

public:
	bool startService(int nPort = 20000);

	bool stopService();
protected:
	
private:

};

#endif // DSS_ICEServiceServer_h__
