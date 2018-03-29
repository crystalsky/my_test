#ifndef LoginCallBackI_h__
#define LoginCallBackI_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "Login.h"

class LoginCallBackI : public Login::LoginCallBack
{
public:
	LoginCallBackI();
	~LoginCallBackI();

public:
	virtual ::std::string getName(const ::Ice::Current& = ::Ice::Current());

	virtual ::std::string getVersion(const ::Ice::Current& = ::Ice::Current());

	virtual void setServerName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

protected:
	
private:
	std::string _strName;
	std::string _strVersion;
	std::string _strServerName;
};

#endif // LoginCallBackI_h__
