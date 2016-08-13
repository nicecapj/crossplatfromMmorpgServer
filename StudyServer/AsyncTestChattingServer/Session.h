#pragma once
#include <cstdio>
#include <iostream>
#include <array>
#include "boost\asio.hpp"
#include "boost\bind.hpp"

#include "Protocol.h"

using boost::asio::ip::tcp;

class TcpServer;
class Session
{	
public:

	Session(boost::asio::io_service& ios, int sessionID, TcpServer* pOwnerServer);
	~Session();

	tcp::socket& Socket() { return socket_;  }

	void PostReceive();
	void PostSend();

	void Initialze();
	void SetSessionID(int id) { sessionID_ = id;  }
	int GetSessionID() {return sessionID_; }

private:
	void HandleWrite(boost::system::error_code, std::size_t);
	void HandleRead(boost::system::error_code, std::size_t);

	tcp::socket socket_;
	std::array<char, MAX_RECEIVE_BUFFER_SIZE> receiveBuffer_;
	std::string writeMessage;

	int sessionID_;

	TcpServer* pOwnerServer_;
};

