#pragma once
#include <cstdio>
#include <iostream>
#include <array>
#include "boost\asio.hpp"
#include "boost\bind.hpp"

using boost::asio::ip::tcp;

class Session
{	
public:

	Session(boost::asio::io_service& ios);
	~Session();

	tcp::socket& Socket() { return socket_;  }

	void PostReceive()
	{
		memset(receiveBuffer_.data(), 0, receiveBuffer_.size());

		socket_.async_read_some(boost::asio::buffer(receiveBuffer_),
			boost::bind(&Session::HandleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

		//c++11
		//socket_.async_read_some(boost::asio::buffer(receiveBuffer_), 
		//	[this](boost::system::error_code error_code, std::size_t bytes_transferred)->void { HandleRead(error_code, bytes_transferred); });
			
	}

private:
	void HandleWrite(boost::system::error_code, std::size_t);
	void HandleRead(boost::system::error_code, std::size_t);

	tcp::socket socket_;
	std::array<char, 128> receiveBuffer_;
	std::string writeMessage;

};

