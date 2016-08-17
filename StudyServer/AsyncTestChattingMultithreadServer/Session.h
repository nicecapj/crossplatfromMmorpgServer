#pragma once
#include <cstdio>
#include <iostream>
#include <array>
#include <deque>
#include <string>
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
	template<typename Packet> 
	void PostSend(Packet* pPacket)
	{		
		PostSend(pPacket->Size, (char*)pPacket);
	}

	void Initialze();
	void SetSessionID(int id) { sessionID_ = id;  }
	int GetSessionID() {return sessionID_; }

	//todo : business logic -> seperate
	void SetName(std::string name) { name_ = name; }
	std::string GetName() { return name_;  }

private:
	void PostSend(const int packetSize, char* pPacket);

	void HandleWrite(boost::system::error_code, std::size_t);
	void HandleRead(boost::system::error_code, std::size_t);

	tcp::socket socket_;
	int sessionID_;

	std::array<char, MAX_RECEIVE_BUFFER_SIZE> receiveBuffer_;	
	
	size_t packetBufferMark_;
	char packetBuffer[MAX_RECEIVE_BUFFER_SIZE * 2];

	std::deque<char*> sendPacketQ_;

	TcpServer* pOwnerServer_;

	std::string name_;
};

