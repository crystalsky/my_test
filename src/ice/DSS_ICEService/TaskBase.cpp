#include "TaskBase.h"

TaskBase::TaskBase(const DSSDataService::DSSServiceCallBackPrx& pxyClient)
	: m_taskInfo(new TaskDataDef::TaskRequest())
	, m_clientPtr(pxyClient)
{
	m_strUserID = m_clientPtr->ice_getIdentity().name;
}

TaskBase::~TaskBase()
{
	
}


std::string TaskBase::getUserID() const
{
	if (m_clientPtr)
	{
		return m_clientPtr->ice_getIdentity().name;
	}
	return "";
}

bool TaskBase::initTaskInfo( const TaskDataDef::TaskRequestPtr& val )
{
	if (val)
	{
		*m_taskInfo = *val; 
		m_strTaskID = val->strTaskID;
		
		if(!parserAdditionalJsonInfo(m_taskInfo->arrAddtionalData))
		{
			return false;
		}

		return true;
	}

	return false;
}

