#ifndef TaskBase_h__
#define TaskBase_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <IceUtil/Monitor.h>
#include "DSSDataService.h"
#include <boost/shared_ptr.hpp>
#include <boost/dynamic_bitset.hpp>

typedef std::string TaskID, UserID;
class TaskBase : public IceUtil::Monitor<IceUtil::Mutex>
{
public:
	TaskBase(const DSSDataService::DSSServiceCallBackPrx& pxyClient);
	~TaskBase();

public:
	//process data???
	virtual bool onRecvData(){return false;}
	virtual bool isHasFinishedRecvData()const{return false;}
	virtual bool onFinish(){return false;}

public:
	TaskID getTaskID()const{return m_strTaskID;}
	std::string getUserID()const;

	const TaskDataDef::TaskRequestPtr& getTaskInfo() const { return m_taskInfo; }
	bool initTaskInfo(const TaskDataDef::TaskRequestPtr& val);
protected:
	virtual bool parserAdditionalJsonInfo(
		const TaskDataDef::ArrayData& jsonData){return true;}
private:
	TaskID	m_strTaskID;
	UserID	m_strUserID;
	TaskDataDef::TaskRequestPtr m_taskInfo;

	DSSDataService::DSSServiceCallBackPrx	m_clientPtr;
};

typedef boost::shared_ptr<TaskBase> TaskPtr;
typedef std::map<TaskID, TaskPtr> MapTasks;

#endif // TaskBase_h__
