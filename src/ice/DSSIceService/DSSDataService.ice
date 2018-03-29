 // **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["cpp:include:Ice/Identity.h"]]
#include "Ice/Identity.ice"

module DSSDataService
{
	enum emTaskType 
	{
		TaskTestDataRecv,
		TaskFileTransfer, 
		TaskCaculate,
		TaskDataTrans,
		TaskOther
	};

	sequence<byte>		ArrayData;
	
	["cpp:class"] struct TaskRequest
	{
		emTaskType 	TaskType;
		string 		strTaskID;
		string 		strTaskUserID;
		ArrayData 	arrAddtionalData;
		int 		nAddtionalDataCRC;
	};

	["cpp:class"] struct TaskRequestResult
	{
		TaskRequest objRequst;
		int 	nResultCode;
		string 	strComment;
	};

	["cpp:class"] struct TaskResultData
	{
		TaskRequestResult objRequestAck;
		ArrayData 		arrPackageData;
		int 			nPackageCRC;
	};

	exception RequestCanceledException
	{
	};

	interface DSSServiceCallBack
	{
		idempotent string getName();
		
		idempotent void setReuestResult(TaskResultData resultData);
	};
	
	interface DSSService
	{
		idempotent bool loginOn(DSSServiceCallBack* pxy);
		idempotent bool loginOff(DSSServiceCallBack* pxy);

		//请求数据
		idempotent bool requestData(Ice::Identity id, TaskRequest request);
	};
};