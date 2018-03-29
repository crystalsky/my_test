#ifndef UserTask_h__
#define UserTask_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <Shared.h>
#include <Handle.h>
#include <boost/shared_ptr.hpp>
#include <boost/dynamic_bitset.hpp>
#include "Login.h"
#include "DataTransmitter.h"
#include <bitset>

typedef std::string TaskID;
class UserTask : public IceUtil::Monitor<IceUtil::Mutex>
{
public:
	UserTask(const Login::LoginCallBackPrx& pxyClient);
	~UserTask();

	TaskID getTaskID()const{return _strTaskID;}
	std::string getUserID()const;

	const DataTransmitter::TaskInfoPtr& getTaskInfo() const { return _taskInfo; }
	void setTaskInfo(const DataTransmitter::TaskInfoPtr& val);

	const DataTransmitter::DataInfoPtr& getDataInfo() const { return _dataInfo; }
	void setDataInfo(const DataTransmitter::DataInfoPtr& val);

	virtual bool checkDataCRC(unsigned int crcCompare)const;

	//初始化附加信息
	virtual bool initialTaskAditionalInfo(const DataTransmitter::ArrayData& jsonArrayData);

	//process data
	virtual bool onRecvData(const DataTransmitter::SendDataPackagePtr& data);
	virtual bool isHasFinishedRecvData()const;
	virtual bool onFinish();

	bool checkCRC32()const;
protected:
	unsigned long getCRC32()const;

protected:
	TaskID	_strTaskID;
	DataTransmitter::ArrayData	_aditionalTaskJsonInfo;
	DataTransmitter::DataInfoPtr _dataInfo;
	DataTransmitter::TaskInfoPtr _taskInfo;
	DataTransmitter::ArrayData	_crcdata;

	int		_nRecvDataSize;

	bool	_isRecvDataFull;

	boost::dynamic_bitset<> _recvIndexSign;

	DataTransmitter::ArrayData	_recvArrayData;
	Login::LoginCallBackPrx	_clientPtr;
};

typedef boost::shared_ptr<UserTask> UserTaskPtr;
typedef std::map<TaskID, UserTaskPtr> MapTasks;
#endif // UserTask_h__
