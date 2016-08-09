#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>

class TcpClient
{
public:
	TcpClient(boost::asio::io_service& ios, const boost::asio::ip::tcp::endpoint& endpoint);
	~TcpClient();

	void Connect();

private:
	void PostWrite();
	void PostReceive();

	//void HandleOnConnect(boost::system::error_code errorcode);	changed to lamda

	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;

	boost::array<char, 128> receiveBuffer_;
	int debugSequenceNumber_;
};

