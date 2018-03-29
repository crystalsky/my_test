// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

module DataTransmitter
{
	sequence<byte>		ArrayData;

	enum emTaskType 
	{
		TaskTestDataRecv,
		TaskFileTransfer, 
		TaskCaculate, 
		TaskOther
	};
	["cpp:class"] struct TaskInfo
	{
		string strTaskID;
		string strTaskUser;
		emTaskType taskType;
	};
	
	["cpp:class"] struct DataInfo
	{
		int nDataTotalSize;
		int nEveryPackSize;
		int nPackageCount;
	};

	struct SendDataInfo
	{
		TaskInfo objTaskInfo;
		ArrayData additionalInfo;
		DataInfo objDataInfo;
	};

	struct CheckDataInfo
	{
		TaskInfo objTaskInfo;
		int nTaskDataCRC;
	};

	//�ļ�������Ϣ
	["cpp:class"] struct SendDataPackage
	{
		string strTaskID;
		int nPackageIndex;
		ArrayData arrData;
		int nPackageCRC;
	};

	exception RequestCanceledException
	{
	};
	
	interface DataProc
	{
	 	//����������Ϣ��(�����÷��͵�����������Ϣ�������첽�������ļ�����)
	    idempotent void setReadySendDataInfo(SendDataInfo dataInfo);
	    //["amd"]idempotent void sendData(SendDataPackage dataPackage)
		//throws RequestCanceledException;
		idempotent void sendData(SendDataPackage dataPackage);
	    	
		idempotent bool checkTaskDataInfo(CheckDataInfo checkInfo);
	};
};
