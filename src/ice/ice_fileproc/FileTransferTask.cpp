#include "FileTransferTask.h"
#include <json.h>
#include <fstream>
#include <FileFunc.h>
#include <glog.h>

FileTransferTask::FileTransferTask(const Login::LoginCallBackPrx& pxyClient)
	: UserTask(pxyClient)
{
	
}

FileTransferTask::~FileTransferTask()
{
	
}

bool FileTransferTask::initialTaskAditionalInfo( const DataTransmitter::ArrayData& jsonArrayData )
{
	if(!UserTask::initialTaskAditionalInfo(jsonArrayData))
	{
		return false;
	}

	std::string strJson(jsonArrayData.begin(), jsonArrayData.end());

	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(strJson, root, false))
	{
		return false;
	}

	std::string strSaveFilePathName = root["SaveFilePathName"].asString();

	const std::string& strFileFullPath = 
		UtilityKit::FileFunc::GetApplicationFileDir() + strSaveFilePathName;

	const std::string& fileDir = UtilityKit::FileFunc::GetDir(strFileFullPath);

	if (!UtilityKit::FileFunc::DirExist(fileDir) &&
		!UtilityKit::FileFunc::CreateDirEx(fileDir))
	{
		return false;
	}
	
	_fileWirter.reset(new std::fstream(strFileFullPath, 
		std::ios::binary | std::ios_base::out));

	if (!_fileWirter->is_open())
	{
		LOG(ERROR) << "Open Wirte File : " << fileDir << "  Failed....";
		return false;
	}

	return true;
}

bool FileTransferTask::onRecvData( const DataTransmitter::SendDataPackagePtr& data )
{
	if (UserTask::onRecvData(data) && data->arrData.size())
	{
		if (_fileWirter->is_open())
		{
			_fileWirter->write((const char*)&data->arrData[0], data->arrData.size());
			_fileWirter->flush();
		}
		return true;
	}
	return false;
}

bool FileTransferTask::isHasFinishedRecvData() const
{
	if (UserTask::isHasFinishedRecvData())
	{
		//TODO check datafile crc



		return true;
	}
	return false;
}

bool FileTransferTask::onFinish()
{
	if (UserTask::onFinish())
	{
		_fileWirter->close();

		return true;
	}

	return false;
}

