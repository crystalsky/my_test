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
#include "Identity.ice"


module Login
{
	interface LoginService
	{
	    idempotent void loginToService(Ice::Identity id);
		idempotent void loginoff(Ice::Identity id);
	};

	interface LoginCallBack
	{
		idempotent string getName();
		idempotent string getVersion();
		idempotent void setServerName(string strServerName);
	};
};
