#pragma once
#include <deque>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>

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

	bool IsConnected() { return socket_.is_open(); }
	bool IsLogin() { return isLogin_; }	

private:	
	void PostSend(const int packetSize, char* pPacket);	
	void PostReceive();

	void HandleRead(boost::system::error_code error_code, size_t bytes_transferred);
	void HandleWrite(boost::system::error_code error_code, size_t bytes_transferred);	


	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;

	boost::array<char, MAX_RECEIVE_BUFFER_SIZE> receiveBuffer_;

	size_t packetBufferMark_ = 0;
	char packetBuffer[MAX_RECEIVE_BUFFER_SIZE * 2];
	std::deque<char*> sendPacketQ_;

	bool isLogin_ = false;		
	boost::mutex mutex_;
};