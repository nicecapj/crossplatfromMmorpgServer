#pragma once

//#include <WinSock2.h>	move stdafx.h

class ClientSession;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO():Object(nullptr)
	{}

	ClientSession* Object;
};

class ClientSession
{
public:
	void OnTick();
	bool OnConnected(SOCKET socket);
	bool PostReceive();

	bool IsConnected();
private:
	SOCKET socket_ = INVALID_SOCKET;
	bool isConnected_ = false;

	SOCKADDR_IN		clientAddr_;	//소켓이 접속 끊기거나 하면 유효하지 않을수 있으니, 정보 표시용으로 저장해둔다

	OverlappedIO overlappedSend_;
	OverlappedIO overlappedRecv_;
};


void CALLBACK RecvCompletion(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
);
void CALLBACK SendCompletion(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
);
