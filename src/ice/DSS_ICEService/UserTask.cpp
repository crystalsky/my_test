#include "UserTask.h"
#include <CRCUtil.h>
#include <glog.h>

UserTask::UserTask(const DSSDataService::DSSServiceCallBackPrx& pxyClient)
	: TaskBase(pxyClient)
	, _nRecvDataSize(0)
{
	
}

UserTask::~UserTask()
{
	
}

bool UserTask::checkDataCRC(unsigned int crcCompare) const
{
	if (_recvArrayData.empty())
	{
		return false;
	}
	unsigned long nCRC = 
		UtilityKit::crc32_UseStaticTable((const char*)&_recvArrayData[0], 
		_recvArrayData.size());

	//unsigned long crcCompare = 0;
	//std::copy(arrCRC.begin(), arrCRC.end(), &crcCompare);

	return nCRC == crcCompare;
}

bool UserTask::onRecvData()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lck(*this);

	/*//comapre data temp crc
	unsigned long nDataCRC = 
		CRCUtil::crc32_UseStaticTable((const char*)&data->arrData[0], 
			data->arrData.size());
	//unsigned long crcCompare = 0;
	//memcpy(&crcCompare, (void*)&data.packageCRC[0], data.packageCRC.size());
	if (nDataCRC != data->nPackageCRC)
	{
		LOG(WARNING) << "Package Data Crc Not Euql...";
	}

	std::copy(data->arrData.begin(), data->arrData.end(), 
		_recvArrayData.begin() + _nRecvDataSize);

	_recvIndexSign.set(data->nPackageIndex);
	
	if (data->arrData.size() == _dataInfo->nEveryPackSize)
	{
		_nRecvDataSize += _dataInfo->nEveryPackSize;
	}
	else
	{
		_nRecvDataSize += data->arrData.size();
	}
	
	_isRecvDataFull = _nRecvDataSize == _dataInfo->nDataTotalSize;*/

	return true;
}

bool UserTask::isHasFinishedRecvData() const
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lck(*this);

	bool bCheckPackageIndex =  _recvIndexSign.all() && 
		!_recvIndexSign.empty() && 
		_isRecvDataFull;

	return bCheckPackageIndex;
}

bool UserTask::onFinish()
{
	if (isHasFinishedRecvData())
	{
		return true;
	}
	return false;
}

bool UserTask::checkCRC32() const
{
	unsigned long nDataCrc32 = getCRC32();
	
	if (_crcdata.empty())
	{
		return false;
	}

	unsigned long orignalCRC = 0;
	if (_crcdata.size() == 4)//crc32
	{
		memcpy(&orignalCRC, &_crcdata[0], _crcdata.size());
	}

	return nDataCrc32 == orignalCRC;
}

unsigned long UserTask::getCRC32() const
{
	if (!_recvArrayData.empty())
	{
		return UtilityKit::crc32_UseStaticTable(
			(const char*)&_recvArrayData[0], _recvArrayData.size());
	}
	return 0;
}

