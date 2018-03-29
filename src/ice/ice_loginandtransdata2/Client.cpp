// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************


#include <sstream>
#include <strstream>
#include <iosfwd>
#include "ProjectPath.h"
#include <UUID.h>
#include "DSSServiceCallBackI.h"
#include <json.h>
#include <boost/program_options.hpp>
#include <sstream>
#include <boost/format.hpp>

namespace po = boost::program_options;
#include <boost/progress.hpp>
using namespace std;

#include <glogInit.h>
#include "../DSS_ICEService/DSS_ICEClient.h"


int main(int argc, char* argv[])
{
 	boost::shared_ptr<glogInit> glog(glogInit::GetInstance());
 	glog->init("ice_fileproc_client");
 
 	boost::shared_ptr<DSS_ICEClient> pClient(new DSS_ICEClient);
 
 	if(pClient->connect("192.168.0.36"))
 	{
 		return -1;
 	}
 
 	pClient->sendTaskDataTransRequest("abcdefg");

	return 0;
}
