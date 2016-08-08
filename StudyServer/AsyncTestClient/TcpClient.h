#pragma once

#include <boost\asio.hpp>

class TcpClient
{
public:
	TcpClient(boost::asio::io_service& ios, const boost::asio::ip::tcp::endpoint& endpoint);
	~TcpClient();

	void Connect();

private:
	//void HandleOnConnect(boost::system::error_code errorcode);	changed to lamda

	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;
};

