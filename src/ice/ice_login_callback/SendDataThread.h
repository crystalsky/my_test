#ifndef SendDataThread_h__
#define SendDataThread_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <IceUtil/IceUtil.h>
#include <glog.h>
#include "DataTransmitter.h"
#include <ThreadSemaphore.h>
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;
#define DEFAULT_EVERYPACK_SIZE 512

namespace DataTransmitterInternal
{
	class SendCallback;
}

typedef std::list<Ice::AsyncResultPtr> ListAsnyResult;
typedef ListAsnyResult::iterator IterAsyncResult;

class SendDataThread : public IceUtil::Thread
{
	friend class DataTransmitterInternal::SendCallback;

	typedef bs2::signal<void (int, int)> signal_ProgressUpdate;
	typedef signal_ProgressUpdate::slot_type SlotProgressUpdater;
public:
	SendDataThread(const DataTransmitter::DataProcPrx& pxyDataProx);
	~SendDataThread();

	bs2::connection connectProgressReport(const SlotProgressUpdater& updater);

	bool setSendData(const char* data, int nSize);
	void setTaskInfo(const DataTransmitter::TaskInfo& taskInfo);
	void setEveryPackageSize(int nEveryPackSize = DEFAULT_EVERYPACK_SIZE);
	void setPackBufferCount(const int& val = 10);

	virtual bool startSend();

	void waitforFinished();

public:
protected:
	virtual void onRespose();

	virtual bool _getSendTaskInfo(DataTransmitter::SendDataInfo& sendDataInfo);
	virtual bool _doSendTaskInfo(const DataTransmitter::SendDataInfo& sendDataInfo);
	virtual bool _doSendRealTaskData(const DataTransmitter::SendDataInfo& sendDataInfo, unsigned int& crcAll)const;
	virtual bool _doSendCheckData(const DataTransmitter::SendDataInfo& sendDataInfo)const;
	void _copyCRC(unsigned int crc, DataTransmitter::ArrayData& crcArray)const;
protected:
	struct progressInfo
	{
		progressInfo(int nTotalSize = 0, int nDataSize = 0)
		{
			this->nTotalSize = nTotalSize;
			this->nDataSize = nDataSize;
		}
		int nDataSize;
		int nTotalSize;
	};
	typedef std::map<int, progressInfo> MapProgressInfo;
	typedef MapProgressInfo::iterator IterMapProgressInfo;
	void updateProgress(const Ice::AsyncResultPtr& ptr, MapProgressInfo& mapInfo)const;
private:
	virtual void run();
private:
	DataTransmitter::DataProcPrx	_prxDataProc;
	DataTransmitter::TaskInfo		_sendTaskInfo;
	int								_nEveryPackageSize;

	char*							_pSendData;
	int								_nSendTotalSize;
	unsigned int					_nTotalDataCRCCode;	//总数据CRC

	unsigned int					_nPackBufferCount;	//发送缓冲数量

	ThreadSemaphore					_threadSemaphore;
	bool							_bCanSendData;

	ThreadSemaphore					_finishSemaphore;

	signal_ProgressUpdate			_progressUpdate;

	IceUtil::Handle<DataTransmitterInternal::SendCallback> _callBackPtr;
};
typedef IceUtil::Handle<SendDataThread> SendDataThreadPtr;
#endif // SendDataThread_h__
