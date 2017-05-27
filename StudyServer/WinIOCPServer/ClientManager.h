#pragma once
#include "Singleton.h"
#include <unordered_map>

class ClientSession;
class ClientManager : public Singleton<ClientManager>
{
public:	
	ClientSession* CreateClient(SOCKET socket);
	void OnTick();
	
	~ClientManager();

	typedef std::unordered_map<SOCKET, ClientSession*> ClientList;

private:
	ClientList clientList_;
};
