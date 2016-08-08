#include "TcpClient.h"
#include <iostream>


TcpClient::TcpClient(boost::asio::io_service& ios,
	const boost::asio::ip::tcp::endpoint&endpoint)
	:io_service_(ios), socket_(ios), endpoint_(endpoint)
{

}

void TcpClient::Connect()
{
	socket_.async_connect(endpoint_, [this](boost::system::error_code errorcode)->void
	{
		if (errorcode)
		{
			std::cout << errorcode.message() << std::endl;
		}
		else
		{
			std::cout << "connected" << std::endl;
		}		
	});
}

TcpClient::~TcpClient()
{
}
