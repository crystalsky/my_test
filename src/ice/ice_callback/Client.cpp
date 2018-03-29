// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Callback.h>
#include "ProjectPath.h"

using namespace std;
using namespace Demo;

class CallbackReceiverI : public CallbackReceiver
{
public:

    virtual void callback(const Ice::Current&)
    {
#ifdef __xlC__
        //
        // The xlC compiler synchronizes cin and cout; to see the messages
        // while accepting input through cin, we have to print the messages
        // with printf
        //
        printf("received callback\n");
        fflush(0);
#else
        cout << "received callback" << endl;
#endif
    }

	virtual void setID(const ::std::string& id, const ::Ice::Current& /* = ::Ice::Current() */)
	{
		this->_ID = id;
		cout << "server set the id" << this->_ID <<endl;;
	}

	std::string getID(const ::Ice::Current& /* = ::Ice::Current() */)
	{
		return this->_ID;
	}

	std::string _ID;
};

class CallbackClient : public Ice::Application
{
public:

    CallbackClient();

    virtual int run(int, char*[]);

private:

    void menu();
};

int
main(int argc, char* argv[])
{
    CallbackClient app;
	std::string strPath = DirPaths::GetIceConfigPath("ice_callback.client");
    return app.main(argc, argv, strPath.c_str());
}

CallbackClient::CallbackClient() :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling)
{
}

int
CallbackClient::run(int argc, char*[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return EXIT_FAILURE;
    }

    CallbackSenderPrx sender = CallbackSenderPrx::checkedCast(
        communicator()->propertyToProxy("CallbackSender.Proxy")->ice_twoway()->ice_timeout(-1)->ice_secure(false));
    if(!sender)
    {
        cerr << appName() << ": invalid proxy" << endl;
        return EXIT_FAILURE;
    }
    
	//TODO 自启一个服务，
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapterWithEndpoints("", "default -h localhost");
    CallbackReceiverPtr cr = new CallbackReceiverI;
    adapter->add(cr, communicator()->stringToIdentity("callbackReceiver1"));
    adapter->activate();

    CallbackReceiverPrx receiver = CallbackReceiverPrx::uncheckedCast(
        adapter->createProxy(communicator()->stringToIdentity("callbackReceiver1")));

    menu();

    char c;
    do
    {
        try
        {
            cout << "==> ";
            cin >> c;
            if(c == 't')
            {
                sender->initiateCallback(receiver);
            }
            else if(c == 's')
            {
                sender->shutdown();
            }
            else if(c == 'x')
            {
                // Nothing to do
            }
            else if(c == '?')
            {
                menu();
            }
            else
            {
                cout << "unknown command `" << c << "'" << endl;
                menu();
            }
        }
        catch(const Ice::Exception& ex)
        {
            cerr << ex << endl;
        }
    }
    while(cin.good() && c != 'x');

    return EXIT_SUCCESS;
}

void
CallbackClient::menu()
{
    cout <<
        "usage:\n"
        "t: send callback\n"
        "s: shutdown server\n"
        "x: exit\n"
        "?: help\n";
}
