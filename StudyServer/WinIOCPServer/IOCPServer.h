#pragma once
class IOCPServer
{
public:
	IOCPServer();
	~IOCPServer();

	bool Initialize(HANDLE iocp, short port);
	void OnTick();
	void Shutdown();

private:
	SOCKET tcpListenSocket_;	
	HANDLE iocp_;
};

