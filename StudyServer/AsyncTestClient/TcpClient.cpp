#include "TcpClient.h"
#include "PlatformDefine.h"
#include <iostream>


TcpClient::TcpClient(boost::asio::io_service& ios,
	const boost::asio::ip::tcp::endpoint&endpoint)
	:io_service_(ios), socket_(ios), endpoint_(endpoint)
{
	debugSequenceNumber_ = 0;
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
			PostWrite();
		}		
	});
}

void TcpClient::PostWrite()
{
	if (!socket_.is_open())
	{
		return;
	}
	
	if (++debugSequenceNumber_ >= 7)
	{
		socket_.close();
		return;
	}

	char buff[128];
	sprintf_s(buff, 128 - 1, "[%d] send message", debugSequenceNumber_);

	boost::asio::async_write(socket_,
		boost::asio::buffer(buff),
		[this](boost::system::error_code error_code, size_t bytes_transferred)
	{

	});

	PostReceive();

}
void TcpClient::PostReceive()
{
	memset(receiveBuffer_.data(), 0, receiveBuffer_.size());

	socket_.async_read_some(boost::asio::buffer(receiveBuffer_),
		[this](boost::system::error_code error_code, size_t bytes_received)
	{
		if (error_code)
		{
			if (error_code == boost::asio::error::eof)
			{
				std::cout << "disconnected with server" << std::endl;
			}
			else
			{
				std::cout << "error No: " << error_code.value() << " error Message: " << error_code.message() << std::endl;
			}
		}
		else
		{
			const std::string message = receiveBuffer_.data();
			std::cout << "messaghe: " << message << ", size: " << bytes_received << std::endl;

			PostWrite();
		}
	});
}

TcpClient::~TcpClient()
{
}
