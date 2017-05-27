#include "stdafx.h"
#include "WS32SocketServer.h"
#pragma comment(lib, "ws2_32.lib")

WS32SocketServer::WS32SocketServer()
{
}


WS32SocketServer::~WS32SocketServer()
{
	Shutdown();
}

bool WS32SocketServer::Initialize(short port)
{
	if (tcpListenSocket_ = socket(AF_INET, SOCK_STREAM, 0) == INVALID_SOCKET)
	{
		return false;
	}

	const int value = 1;
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(int)) < 0)
	{
		return false;
	}

	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_KEEPALIVE, (char*)&value, sizeof(int)) < 0)
	{
		return false;
	}

	linger ling = { 1, 0 };
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(linger)) < 0)
	{
		return false;
	}


	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = port;

	if (bind(tcpListenSocket_, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		Shutdown();
		return false;
	}

	if (listen(tcpListenSocket_, SOMAXCONN) < 0)
	{
		Shutdown();
		return false;
	}

	return true;
}

void WS32SocketServer::Shutdown()
{
	closesocket(tcpListenSocket_);
	tcpListenSocket_ = INVALID_SOCKET;
}