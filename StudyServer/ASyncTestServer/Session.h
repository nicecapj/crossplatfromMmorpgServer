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

	Session(boost::asio::io_service& ios):socket_(ios) 
	{}

	~Session();

	tcp::socket& Socket() { return socket_;  }

	void PostReceive()
	{
		memset(receiveBuffer.data(), 0, receiveBuffer.size());

		socket_.async_read_some(boost::asio::buffer(receiveBuffer),
			boost::bind(&Session::HandleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

		//c++11
		//socket_.async_read_some(boost::asio::buffer(receiveBuffer), [this](boost::system::error_code, std::size_t)->void{});
			
	}

private:
	void HandleWrite(boost::system::error_code, std::size_t);
	void HandleRead(boost::system::error_code, std::size_t);

	tcp::socket socket_;
	std::array<char, 128> receiveBuffer;
	

};

