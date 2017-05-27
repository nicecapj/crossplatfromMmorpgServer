#include "stdafx.h"
#include "ClientManager.h"
#include "ClientSession.h"

ClientSession* ClientManager::CreateClient(SOCKET socket)
{
	ClientSession* newSession = new ClientSession();
	if (newSession == nullptr)
		return nullptr;
	
	clientList_.insert(ClientList::value_type(socket, newSession));	

	return newSession;
}

void ClientManager::OnTick()
{
}

ClientManager::~ClientManager()
{
	for (auto client : clientList_)
	{
		delete client.second;
	}
	clientList_.clear();
}
