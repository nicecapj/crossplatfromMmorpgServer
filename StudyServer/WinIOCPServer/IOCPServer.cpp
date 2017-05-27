#include "stdafx.h"
#include "IOCPServer.h"
#include "ClientManager.h"
#include "ClientSession.h"
#pragma comment(lib, "ws2_32.lib")

IOCPServer::IOCPServer()
{
}


IOCPServer::~IOCPServer()
{
	Shutdown();
}

bool IOCPServer::Initialize(HANDLE iocp, short port)
{	
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;

	tcpListenSocket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (tcpListenSocket_ == INVALID_SOCKET)
	{
		return false;
	}

	int value = 1;
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_REUSEADDR, (const char*)&value, sizeof(int)) < 0)
	{
		return false;
	}

	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_KEEPALIVE, (const char*)&value, sizeof(int)) < 0)
	{
		return false;
	}

	linger ling = { 1, 0 };
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_LINGER, (const char*)&ling, sizeof(linger)) < 0)
	{
		return false;
	}


	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (bind(tcpListenSocket_, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		Shutdown();
		return false;
	}

	if (listen(tcpListenSocket_, SOMAXCONN) < 0)
	{
		Shutdown();
		return false;
	}

	iocp_ = iocp;

	return true;
}

void IOCPServer::OnTick()
{
	SOCKET acceptedSocket = accept(tcpListenSocket_, NULL, NULL);
	if (acceptedSocket == INVALID_SOCKET)
	{
		return;
	}

	auto client = ClientManager::Get()->CreateClient(acceptedSocket);
	if (client != nullptr)
	{
		client->OnConnected(acceptedSocket);
	}


}


void IOCPServer::Shutdown()
{	
	closesocket(tcpListenSocket_);
	tcpListenSocket_ = INVALID_SOCKET;

	WSACleanup();
}
