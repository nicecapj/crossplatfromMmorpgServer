#pragma once
class IOCPServer
{
public:
	IOCPServer();
	~IOCPServer();

	void Initialize(short port);
	void Shutdown();

private:
	SOCKET tcpListenSocket_;
};

