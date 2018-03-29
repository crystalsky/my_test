#include "ClientsManager.h"
#include <glog.h>
#include "Ice\Proxy.h"
#include "Ice\Connection.h"

ClientsManager::ClientsManager()
{
	_timerHeartBeat = new IceUtil::Timer();
	_timerHeartBeat->scheduleRepeated(this, IceUtil::Time::seconds(2));
}

ClientsManager::~ClientsManager()
{
	
}

bs2::connection ClientsManager::connectOnLoseConnection(const onLossConnection::slot_type& func )
{
	return _sigLossConnection.connect(func);
}

bool ClientsManager::addClientPrx( const Ice::Identity& id, const Login::LoginCallBackPrx& prx )
{
	//testid
	bool bEqual = id == prx->ice_getIdentity();
	
	LOG(INFO) 
		<< "\n	 Connect Client:" << prx->ice_getConnection()->toString() 
		<< "\n   UserID:" <<id.name;

	//
	IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
	if (_mapClients.find(id) != _mapClients.end())
	{
		return false;
	}

	_mapClients[id] = prx;

	return true;
}

void ClientsManager::removeClientPrx( const Ice::Identity& id )
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);

	MapClients::iterator iterFind =
		_mapClients.find(id);
	if (iterFind != _mapClients.end())
	{
		_mapClients.erase(id);
	}
}

Login::LoginCallBackPrx ClientsManager::FindClientByID( const std::string& strUserID ) const
{
	MapClients temp;
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
		temp = _mapClients;
	}
	Ice::Identity iden;
	iden.name = strUserID;
	
	MapClients::iterator iterFind =
		temp.find(iden);
	if (iterFind != temp.end())
	{
		return iterFind->second;
	}
	return Login::LoginCallBackPrx();
}

void ClientsManager::runTimerTask()
{
	MapClients temp;
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
		temp = _mapClients;
	}

	for (MapClients::iterator iter = temp.begin();
		iter != temp.end(); )
	{
		try
		{
			const std::string strClientName = 
				iter->second->getName();
			iter->second->setServerName("This is Server");

			//std::cout << "Sending To Client HeartBeat:" << strClientName;
			++iter;
		}
		catch(const Ice::Exception& ex)
		{
			std::cerr << "removing client `" << iter->first.name << "':\n"
				<< ex << std::endl;

			_sigLossConnection(iter->first.name);

			iter = temp.erase(iter);
		}
	}

	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
		_mapClients = temp;
	}
}

