#include "LoginCallBackI.h"

LoginCallBackI::LoginCallBackI()
	: _strName("my name is Client")
{
	
}

LoginCallBackI::~LoginCallBackI()
{
	
}

::std::string LoginCallBackI::getName( const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	return _strName;
}

::std::string LoginCallBackI::getVersion( const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	return _strVersion;
}

void LoginCallBackI::setServerName( const ::std::string& name, const ::Ice::Current& /*= ::Ice::Current()*/ )
{
	_strServerName = name;
	std::cout << "Server Heartbeat..." << std::endl;
}

