#include "TaskDataTrans.h"

TaskDataTrans::TaskDataTrans(const DSSDataService::DSSServiceCallBackPrx& pxyClient)
	: TaskBase(pxyClient)
{
	
}

TaskDataTrans::~TaskDataTrans()
{
	
}

bool TaskDataTrans::parserAdditionalJsonInfo( 
	const TaskDataDef::ArrayData& jsonData )
{
	return true;
}

