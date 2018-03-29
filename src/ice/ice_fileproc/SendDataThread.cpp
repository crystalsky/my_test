#include "SendDataThread.h"
#include <boost/timer.hpp>
#include "CRCUtil.h"

namespace DataTransmitterInternal
{
	typedef IceUtil::Handle<SendDataThread> SendDataThreadPtr;
	class SendCallback : public IceUtil::Shared
	{
	public:
		SendCallback(const SendDataThreadPtr& ptr)
			: _threadPtr(ptr)
		{
			assert(_threadPtr != NULL);
		}

		void response()
		{
			if (_threadPtr)
			{
				_threadPtr->onRespose();
			}
		}

		void exception(const Ice::Exception& ex)
		{
			std::cerr << "" << ex << std::endl;
		}
	private:
		SendDataThreadPtr _threadPtr;
	};
	typedef IceUtil::Handle<SendCallback> SendCallbackPtr;
}

SendDataThread::SendDataThread(const DataTransmitter::DataProcPrx& pxyDataProx)
	: _prxDataProc(pxyDataProx)
	, _nEveryPackageSize(DEFAULT_EVERYPACK_SIZE)
	, _threadSemaphore(0)
	, _finishSemaphore(0)
	, _pSendData(0)
	, _nSendTotalSize(0)
	, _bCanSendData(false)
	, _nPackBufferCount(10)
	, _nTotalDataCRCCode(0)
	, _callBackPtr(new DataTransmitterInternal::SendCallback(this))
{
	assert(_prxDataProc != NULL);
}

SendDataThread::~SendDataThread()
{
	if (_pSendData)
	{
		delete []_pSendData;
		_pSendData = NULL;
	}
}

bs2::connection SendDataThread::connectProgressReport( const SlotProgressUpdater& updater )
{
	return _progressUpdate.connect(updater);
}

bool SendDataThread::setSendData( const char* data, int nSize )
{
	if (data == NULL || nSize <= 0)
	{
		LOG(ERROR) << "Error Data Parameter...";
		return false;
	}

	_pSendData = const_cast<char*>(data);
	_nSendTotalSize = nSize;

	return true;
}

void SendDataThread::setTaskInfo( const DataTransmitter::TaskInfo& taskInfo )
{
	_sendTaskInfo = taskInfo;
}

void SendDataThread::setEveryPackageSize( int nEveryPackSize )
{
	if (nEveryPackSize <= 100)
	{
		nEveryPackSize = 100;
	}
	_nEveryPackageSize = nEveryPackSize;
}

void SendDataThread::setPackBufferCount( const int& val /*= 10*/ )
{
	if (val < 10)
	{
		_nPackBufferCount = 10;
	}
	_nPackBufferCount = val;
}

bool SendDataThread::startSend()
{
	if (_sendTaskInfo.strTaskID.empty() ||
		_sendTaskInfo.strTaskUser.empty())
	{
		LOG(ERROR) << "SendData Has No Task Info....";
		return false;
	}
	if (!_prxDataProc)
	{
		LOG(ERROR) << "Invalide DataProxy....";
		return false;
	}
	IceUtil::Thread::start();
	return true;
}

void SendDataThread::waitforFinished()
{
	do {} while (!_finishSemaphore.Acquire(100));
}

void SendDataThread::onRespose()
{
	_threadSemaphore.Release();
}

void SendDataThread::run()
{
	DataTransmitter::SendDataInfo sendDataInfo;
	if (!_getSendTaskInfo(sendDataInfo))
	{
		LOG(ERROR) << "Task Info Get Failed....";
		return;
	}

	boost::timer t;

	if(!_doSendTaskInfo(sendDataInfo))
	{
		LOG(ERROR) << "Send TaskInfo Failed....";
		return;
	}

	//init crc
	_nTotalDataCRCCode = CRCUtil::g_nCRCFirstVal;

	//do send real datas and get the datacrc
	_doSendRealTaskData(sendDataInfo, _nTotalDataCRCCode);

	int nt = CRCUtil::crc32_UseStaticTable(
		_pSendData, _nSendTotalSize);

	//do check the all data crc
	_doSendCheckData(sendDataInfo);


	LOG(INFO) << "\n   Send Data:" << _nSendTotalSize 
		<<"   EveryPackSize:" << _nEveryPackageSize << "\n"
		<<"   PackageBufferCount:" << _nPackBufferCount << "\n"
		<<"   UseTime:" << t.elapsed() << std::endl;
	_finishSemaphore.Release();
}

bool SendDataThread::_doSendTaskInfo(const DataTransmitter::SendDataInfo& sendDataInfo)
{
	Ice::AsyncResultPtr ptrDataInfoResult = 
		_prxDataProc->begin_setReadySendDataInfo(sendDataInfo);
	ptrDataInfoResult->waitForCompleted();

	return ptrDataInfoResult->isCompleted();
}

bool SendDataThread::_doSendRealTaskData(
	const DataTransmitter::SendDataInfo& sendDataInfo,
	unsigned int& crcAll)const
{
	if (!sendDataInfo.objDataInfo)
	{
		return false;
	}

	SendDataThread* pThis = const_cast<SendDataThread*>(this);
	DataTransmitterInternal::SendCallbackPtr callBack = 
		new DataTransmitterInternal::SendCallback(pThis);

	//caculate the last package size
	const int nLastPackageSize = 
		sendDataInfo.objDataInfo->nDataTotalSize % 
		sendDataInfo.objDataInfo->nEveryPackSize;

	//Wait The Server TaskCreate ACK
	MapProgressInfo mapSendHashDataSize;
	ListAsnyResult listAsyncResult;

	//loop send data start...
	int nSendOffset = 0;
	for (int i = 0; i < sendDataInfo.objDataInfo->nPackageCount; ++i)
	{
		DataTransmitter::SendDataPackagePtr sdpkg(new DataTransmitter::SendDataPackage);
		sdpkg->strTaskID = sendDataInfo.objTaskInfo->strTaskID;
		sdpkg->nPackageIndex = i;

		//defautl use EveryPackageSize
		int nReadSize = _nEveryPackageSize;

		//use nLastPackageSize when it's on last package index
		if (i == sendDataInfo.objDataInfo->nPackageCount - 1)
		{
			nReadSize = nLastPackageSize;
		}
		sdpkg->arrData.resize(nReadSize);
		std::copy(_pSendData + nSendOffset, 
			_pSendData + nSendOffset + nReadSize,
			sdpkg->arrData.begin());

		sdpkg->nPackageCRC = CRCUtil::crc32_UseStaticTable(
			_pSendData + nSendOffset, nReadSize);

		//crc32
		crcAll = CRCUtil::crc32_UseStaticTable(
			crcAll, _pSendData + nSendOffset, nReadSize);

		nSendOffset += nReadSize;
		//_copyCRC(pkg_crc32, sdpkg.packageCRC);

		//send data method...
		Ice::AsyncResultPtr ptrResult = _prxDataProc->begin_sendData(sdpkg, 
			DataTransmitter::newCallback_DataProc_sendData(callBack, 
			&DataTransmitterInternal::SendCallback::response,
			&DataTransmitterInternal::SendCallback::exception));
		listAsyncResult.push_back(ptrResult);

		mapSendHashDataSize.insert(
			std::make_pair(ptrResult->getHash(), progressInfo(_nSendTotalSize, nReadSize)));

		while(listAsyncResult.size() > _nPackBufferCount)
		{
			Ice::AsyncResultPtr ptrResultWait = listAsyncResult.front();
			ptrResultWait->waitForCompleted();
			updateProgress(ptrResultWait, mapSendHashDataSize);
			listAsyncResult.pop_front();
		}
	}

	while (!listAsyncResult.empty())
	{
		Ice::AsyncResultPtr ptrResultWait = listAsyncResult.front();
		ptrResultWait->waitForCompleted();
		updateProgress(ptrResultWait, mapSendHashDataSize);
		listAsyncResult.pop_front();
	} 

	return true;
}

bool SendDataThread::_doSendCheckData( const DataTransmitter::SendDataInfo& sendDataInfo ) const
{
	DataTransmitter::CheckDataInfo checkData;
	checkData.objTaskInfo = new DataTransmitter::TaskInfo(*sendDataInfo.objTaskInfo);
	checkData.nTaskDataCRC = _nTotalDataCRCCode;
	//_copyCRC(_nTotalDataCRCCode, checkData.arrCRC);

	Ice::AsyncResultPtr ptrDataInfoResult = 
		_prxDataProc->begin_checkTaskDataInfo(checkData);
	ptrDataInfoResult->waitForCompleted();

	bool bDataCheckOk = _prxDataProc->end_checkTaskDataInfo(ptrDataInfoResult);

	return ptrDataInfoResult->isCompleted();
}

void SendDataThread::updateProgress( const Ice::AsyncResultPtr& ptr, MapProgressInfo& mapInfo ) const
{
	IterMapProgressInfo iter = mapInfo.find(ptr->getHash());
	if (iter != mapInfo.end())
	{
		_progressUpdate(
			iter->second.nTotalSize, iter->second.nDataSize);
		mapInfo.erase(iter);
	}
	else
	{
		LOG(WARNING) << "No AsyncResult Hash Value Find....";
	}
}

bool SendDataThread::_getSendTaskInfo( DataTransmitter::SendDataInfo& sendDataInfo )
{
	DataTransmitter::DataInfo objDataInfo;
	objDataInfo.nDataTotalSize = _nSendTotalSize;
	const int nLastPackageSize = objDataInfo.nDataTotalSize % _nEveryPackageSize;
	objDataInfo.nPackageCount = nLastPackageSize == 0 ?
		objDataInfo.nDataTotalSize / _nEveryPackageSize : 
	objDataInfo.nDataTotalSize / _nEveryPackageSize + 1;
	objDataInfo.nEveryPackSize = _nEveryPackageSize;

	sendDataInfo.objTaskInfo = new DataTransmitter::TaskInfo(_sendTaskInfo);
	sendDataInfo.objDataInfo = new DataTransmitter::DataInfo(objDataInfo);

	return true;
}

void SendDataThread::_copyCRC( 
	unsigned int crc, 
	DataTransmitter::ArrayData& crcArray ) const
{
	crcArray.clear();
	crcArray.resize(4);
	memcpy(&crcArray[0], &crc, sizeof(int));
}

