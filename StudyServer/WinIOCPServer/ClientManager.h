#pragma once
#include "Singleton.h"
#include <mutex>
#include <unordered_map>

class ClientSession;
class ClientManager : public Singleton<ClientManager>
{
public:	
	ClientSession* CreateClient(SOCKET socket);
	void DeleteClient(ClientSession* client);
	void OnTick();
	void FlushClientSend();
	
	~ClientManager();

	typedef std::unordered_map<SOCKET, ClientSession*> ClientList;

private:
	ClientList clientList_;
	std::mutex clientListLock_;
};
