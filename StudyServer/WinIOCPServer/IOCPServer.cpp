#include "stdafx.h"
#include "IOCPServer.h"
#pragma comment(lib, "ws2_32.lib")

IOCPServer::IOCPServer()
{
}


IOCPServer::~IOCPServer()
{
	Shutdown();
}

void IOCPServer::Initialize(short port)
{
	if (tcpListenSocket_ = socket(AF_INET, SOCK_STREAM, 0) == INVALID_SOCKET)
	{
		return;
	}

	const int value = 1;
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(int)) < 0)
	{
		return;
	}

	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_KEEPALIVE, (char*)&value, sizeof(int)) < 0)
	{
		return;
	}

	linger ling = { 1, 0 };
	if (setsockopt(tcpListenSocket_, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(linger)) < 0)
	{
		return;
	}


	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = port;

	if (bind(tcpListenSocket_, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		Shutdown();
		return;
	}

	if (listen(tcpListenSocket_, SOMAXCONN) < 0)
	{
		Shutdown();
		return;
	}

}

void IOCPServer::Shutdown()
{
	closesocket(tcpListenSocket_);
	tcpListenSocket_ = INVALID_SOCKET;
}
