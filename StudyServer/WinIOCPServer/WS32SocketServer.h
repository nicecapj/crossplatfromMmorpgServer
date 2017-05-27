#pragma once
class WS32SocketServer
{
public:
	WS32SocketServer();
	~WS32SocketServer();

	bool Initialize(short port);
	void Shutdown();

private:
	SOCKET tcpListenSocket_;
};

