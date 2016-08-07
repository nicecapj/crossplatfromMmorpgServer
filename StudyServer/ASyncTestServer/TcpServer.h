#pragma once

#include<boost\asio.hpp>


using boost::asio::io_service;
using boost::asio::ip::tcp;
class Session;

class TcpServer
{
public:
	TcpServer(io_service& io_service);
	virtual ~TcpServer();

	///bind -> listen -> accept
	void StarAccept();

private:
	void HandleAccept(Session* pSession, const boost::system::error_code& error_code);

	Session* pSession_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

