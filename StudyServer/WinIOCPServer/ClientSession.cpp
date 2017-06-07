#include "stdafx.h"
#include "ClientSession.h"
#include "Logger.h"

void ClientSession::OnTick()
{
}

bool ClientSession::OnConnected(SOCKET socket)
{	
	std::lock_guard<std::mutex> lock(clientLock_);
	socket_ = socket;
	u_long arg = 1;
	ioctlsocket(socket_, FIONBIO, &arg);
	
	int opt = 1;
	setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&opt), sizeof(int));	


	//LOG
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(socket, (SOCKADDR*)&clientaddr, &addrlen);

	memcpy(&clientAddr_, &clientaddr, sizeof(clientaddr));

	Logger::Log(Logger::Normal, "[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa(clientAddr_.sin_addr), ntohs(clientAddr_.sin_port));

	isConnected_ = true;
	
	return PostReceive();
}

bool ClientSession::PostReceive()
{
	if (!IsConnected())
		return false;

	memset(&overlappedRecv_, 0, sizeof(overlappedRecv_));
	overlappedRecv_.Object = this;
	
	//todo : make ring buffer
	WSABUF buff;
	DWORD recvBytes = 0;
	DWORD flags = 0;
	int ret = WSARecv(socket_, &buff, 1, &recvBytes, &flags, &overlappedRecv_, &RecvCompletion);
	if (ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSA_IO_PENDING)
		{
			return false;
		}
	}

	return true;
}

bool ClientSession::IsConnected()
{
	return false;
}

void ClientSession::Disconnect()
{
	std::lock_guard<std::mutex> lock(clientLock_);

	if (!IsConnected())
		return;

	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;

	if (SOCKET_ERROR == setsockopt(socket_, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{		
		return;
	}

	closesocket(socket_);
	
	isConnected_ = false;
}

SOCKET ClientSession::GetSocket() const
{
	return socket_;	
}

void CALLBACK RecvCompletion(IN DWORD dwError, IN DWORD cbTransferred, IN LPWSAOVERLAPPED lpOverlapped, IN DWORD dwFlags)
{
}

void CALLBACK SendCompletion(IN DWORD dwError, IN DWORD cbTransferred, IN LPWSAOVERLAPPED lpOverlapped, IN DWORD dwFlags)
{
}
