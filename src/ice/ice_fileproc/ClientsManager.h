#ifndef ClientsManager_h__
#define ClientsManager_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <IceUtil/IceUtil.h>
#include "Login.h"
#include "IceUtil/Timer.h"
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

class ClientsManager : public IceUtil::TimerTask,
	public ::IceUtil::Monitor< ::IceUtil::Mutex>
{
	typedef bs2::signal<void (const std::string&)> onLossConnection;
	friend class HeartBeatTask;
public:
	ClientsManager();
	~ClientsManager();

	bs2::connection connectOnLoseConnection(const onLossConnection::slot_type& func);
public:
	bool addClientPrx(const Ice::Identity& id, const Login::LoginCallBackPrx& prx);
	void removeClientPrx(const Ice::Identity& id);

	Login::LoginCallBackPrx FindClientByID(const std::string& strUserID)const;
protected:
	void runTimerTask();
private:
	typedef std::map<Ice::Identity, Login::LoginCallBackPrx> MapClients;
	MapClients _mapClients;
	IceUtil::TimerPtr _timerHeartBeat;

	onLossConnection	_sigLossConnection;
};

typedef IceUtil::Handle<ClientsManager> ClientsManagerPtr;

#endif // ClientsManager_h__
