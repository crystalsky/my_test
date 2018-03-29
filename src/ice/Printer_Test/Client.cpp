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
#include "Printer.h"
#include "PrinterCallBackI.h"
#include <IceUtil/UUID.h>

using namespace std;

int
main(int argc, char* argv[])
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
		Demo::PrinterPrx print = 
			Demo::PrinterPrx::checkedCast(
			_CommunicatorPtr->stringToProxy("SimplePrinter:default -h localhost -p 10000")->ice_twoway()->ice_timeout(-1)->ice_secure(false));

		print->printString("abcdefg");
		{
			//TODO 自启一个服务，
			Ice::ObjectAdapterPtr adapter = _CommunicatorPtr->createObjectAdapterWithEndpoints("", "default -h localhost");
			Demo::PrinterCallBackPtr cr = new PrinterCallBackI;
			adapter->add(cr, _CommunicatorPtr->stringToIdentity("111"));
			adapter->activate();

			Demo::PrinterCallBackPrx receiver = Demo::PrinterCallBackPrx::uncheckedCast(
				adapter->createProxy(_CommunicatorPtr->stringToIdentity("111")));


			print->addClient(receiver);
		}
		
		Sleep(3000);

		_CommunicatorPtr->shutdown();
		// Server implementation here ...
	} 
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
		return 1;
	}
	return 0;

   return 0;
}

