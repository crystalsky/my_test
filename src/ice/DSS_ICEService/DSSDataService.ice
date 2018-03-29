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

#include "TaskDataDef.ice"

module DSSDataService
{
	
	interface DSSServiceCallBack
	{
		idempotent string getName();
		
		idempotent void setReuestResult(TaskDataDef::TaskResultData resultData);
	};
	
	interface DSSService
	{
		idempotent bool loginOn(DSSServiceCallBack* pxy);
		idempotent bool loginOff(DSSServiceCallBack* pxy);

		//请求数据
		idempotent TaskDataDef::emRequestResultType requestData(TaskDataDef::TaskRequest request);
	};
};