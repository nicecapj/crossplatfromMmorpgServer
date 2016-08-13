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
	TcpServer(io_service& io_service);
	virtual ~TcpServer();

	void Initialize(int maxConnection);
	///bind -> listen -> accept
	bool PostAccept();

private:
	void HandleAccept(Session* pSession, const boost::system::error_code& error_code);

	std::vector<Session*> sessionList_;	
	std::queue<int> sessionQ_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

