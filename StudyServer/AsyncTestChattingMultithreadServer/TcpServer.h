#pragma once

#include<vector>
#include<queue>
#include<boost\asio.hpp>


using boost::asio::io_service;
using boost::asio::ip::tcp;
class Session;

class TcpServer
{
public:
	TcpServer(io_service& io_service, unsigned short potNum);
	virtual ~TcpServer();

	void Initialize(int maxConnection);
	void Start();

	
	void ProcessPacket(const int sessionID, const char* pPacketData);
	void CloseSession(int sessionID);

private:
	///bind -> listen -> accept	
	bool PostAccept();

	void HandleAccept(Session* pSession, const boost::system::error_code& error_code);

	std::vector<Session*> sessionList_;	
	std::queue<int> sessionQ_;
	boost::asio::ip::tcp::acceptor acceptor_;

	bool hasSession = false;

	int packetProcessCount_;
};

