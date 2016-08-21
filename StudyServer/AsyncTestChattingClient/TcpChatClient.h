#pragma once
#include <deque>
#include <thread>
#include <array>
#include <mutex>

#include <boost/asio.hpp>
//#include <boost/array.hpp>
//#include <boost/thread.hpp>

#include "../AsyncTestChattingServer/Protocol.h"

class TcpChatClient
{
public:
	TcpChatClient(boost::asio::io_service& ios, const boost::asio::ip::tcp::endpoint& endpoint);
	~TcpChatClient();

	void Connect();
	void Close();

	template<typename Packet>
	void PostSend(Packet* pPacket)
	{
		PostSend(pPacket->Size, (char*)pPacket);
	}

	void ProcessPacket(const char*pData);

	//bool IsConnected() { return socket_.is_open(); }	//is_open() is not return connected_server. only valid socket.
	bool IsValidSocket() { return socket_.is_open(); }
	bool IsConnectedServer() { return isConnectedServer_;  }
	bool IsLoggedin() { return isLogin_; }	

private:	
	void PostSend(const int packetSize, char* pPacket);	
	void PostReceive();

	void HandleRead(boost::system::error_code error_code, size_t bytes_transferred);
	void HandleWrite(boost::system::error_code error_code, size_t bytes_transferred);	


	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;

	std::array<char, MAX_RECEIVE_BUFFER_SIZE> receiveBuffer_;

	size_t packetBufferMark_ = 0;
	char packetBuffer[MAX_RECEIVE_BUFFER_SIZE * 2];
	std::deque<char*> sendPacketQ_;

	bool isLogin_ = false;		
	bool isConnectedServer_ = false;	
	
	std::recursive_mutex mutex_;	

	int debugSendCount_ = 0;
};