#ifndef TaskDataTrans_h__
#define TaskDataTrans_h__

#include "TaskBase.h"

class TaskDataTrans : public TaskBase
{
public:
	TaskDataTrans(const DSSDataService::DSSServiceCallBackPrx& pxyClient);
	~TaskDataTrans();

public:
	
protected:
	virtual bool parserAdditionalJsonInfo(
		const TaskDataDef::ArrayData& jsonData);
private:

};

#endif // TaskDataTrans_h__
