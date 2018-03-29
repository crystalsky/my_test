#ifndef LoginI_h__
#define LoginI_h__

#include "Login.h"
#include "ClientsManager.h"

class LoginI : virtual public Login::LoginService
{
public:

    LoginI(const ClientsManagerPtr& manager);

    virtual void loginToService(const ::Ice::Identity& id, const ::Ice::Current& cur);
	virtual void loginoff(const ::Ice::Identity& id, const ::Ice::Current& cur);
private:
	ClientsManagerPtr m_ClientsManagerPtr;
};


#endif // LoginI_h__
