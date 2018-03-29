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

[["cpp:header-ext:h"]]

module TaskDataDef
{
	enum emTaskType 
	{
		TaskTestDataRecv,
		TaskFileTransfer, 
		TaskCaculate,
		TaskDataTrans,
		TaskOther
	};

	enum emRequestResultType 
	{
		RTNoError,
		RTAdditionalDataCRCFailed,
		RTInvalideClientID, 
		RTCreateTaskFaild
	};

	sequence<byte>		ArrayData;
	
	["cpp:class"] struct TaskRequest
	{
		emTaskType 		TaskType;
		string 			strTaskID;
		Ice::Identity 	userID;
		ArrayData 		arrAddtionalData;
		long 			nAddtionalDataCRC;
	};

	["cpp:class"] struct TaskRequestResult
	{
		TaskRequest     objRequst;
		int 			nResultCode;
		string 	        strComment;
	};

	["cpp:class"] struct TaskResultData
	{
		TaskRequestResult objRequestAck;
		ArrayData 		arrPackageData;
		int 			nPackageCRC;
	};
};

