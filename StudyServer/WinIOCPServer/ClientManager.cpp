#include "stdafx.h"
#include "ClientManager.h"
#include "ClientSession.h"

ClientSession* ClientManager::CreateClient(SOCKET socket)
{
	ClientSession* newSession = new ClientSession();
	if (newSession == nullptr)
		return nullptr;
	
	//todo : add lock	
	std::lock_guard<std::mutex> lock(clientListLock_);
	clientList_.insert(ClientList::value_type(socket, newSession));	

	return newSession;
}

void ClientManager::DeleteClient(ClientSession * client)
{
	std::lock_guard<std::mutex> lock(clientListLock_);
	clientList_.erase(client->GetSocket());

	delete client;
}

void ClientManager::OnTick()
{
}

void ClientManager::FlushClientSend()
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
