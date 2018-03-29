// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "ProjectPath.h"
#include <PrinterI.h>
using namespace std;

int main(int argc, char* argv[])
{
	Ice::CommunicatorPtr _CommunicatorPtr;
	try
	{
		char** argv = new char*[1];
		argv[0] = new char[200];
		strcpy(argv[0] , "--Ice.MessageSizeMax=10240000");
		int argc = 1;
		if(_CommunicatorPtr == NULL)
			_CommunicatorPtr = Ice::initialize(argc, argv);
		assert(_CommunicatorPtr != NULL);

		delete[] argv[0];
		delete[] argv;

		//////////////////////////////////////////////////////////////////////////
		Ice::ObjectAdapterPtr adapter =

		_CommunicatorPtr->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "default -p 10000");
		Ice::ObjectPtr object = new PrinterI;

		adapter->add(object, _CommunicatorPtr->stringToIdentity("SimplePrinter"));
		adapter->activate();
		_CommunicatorPtr->waitForShutdown();

		// Server implementation here ...
	} 
	catch(const std::exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	return 0;

	return 0;

}
