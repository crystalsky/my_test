#ifndef UserTask_h__
#define UserTask_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <Shared.h>
#include <Handle.h>
#include "DSSDataService.h"
#include <bitset>
#include "TaskBase.h"

typedef std::string TaskID;
class UserTask : public TaskBase
{
public:
	UserTask(const DSSDataService::DSSServiceCallBackPrx& pxyClient);
	~UserTask();

	virtual bool onRecvData();
	virtual bool isHasFinishedRecvData()const;
	virtual bool onFinish();

	virtual bool checkDataCRC(unsigned int crcCompare)const;

	bool checkCRC32()const;
protected:
	unsigned long getCRC32()const;


protected:
	TaskDataDef::ArrayData	_crcdata;

	int		_nRecvDataSize;

	bool	_isRecvDataFull;

	boost::dynamic_bitset<> _recvIndexSign;

	TaskDataDef::ArrayData	_recvArrayData;
	DSSDataService::DSSServiceCallBackPrx	_clientPtr;
};

#endif // UserTask_h__
