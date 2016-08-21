#include "Session.h"
#include <string>

#include "TcpServer.h"
#include "Logger.h"

Session::Session(boost::asio::io_service& ios, int sessionID, TcpServer* pOwnerServer)
	:socket_(ios),
	sessionID_(sessionID),
	pOwnerServer_(pOwnerServer)
{	
	packetBufferMark_ = 0;			
}

Session::~Session()
{
	if (socket_.is_open())
	{
		socket_.close();
	}

	if (!sendPacketQ_.empty())
	{
		delete[] sendPacketQ_.front();
		sendPacketQ_.pop_front();
	}
}

void Session::Initialze()
{

}

void Session::PostReceive()
{	
 	socket_.async_read_some(boost::asio::buffer(receiveBuffer_),
		boost::bind(&Session::HandleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));	
}

void Session::PostSend(const int packetSize, char* pPacket)
{	
	std::unique_lock<std::recursive_mutex> guard(mutex_);

	char* pSendPacket = new char[packetSize];
	memcpy(pSendPacket, pPacket, packetSize);

	sendPacketQ_.push_back(pSendPacket);

	boost::asio::async_write(socket_,  
		boost::asio::buffer(pSendPacket, packetSize),
		boost::bind(&Session::HandleWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::HandleWrite(boost::system::error_code error_code, std::size_t bytes_transferred)
{
	std::unique_lock<std::recursive_mutex> guard(mutex_);

	delete[] sendPacketQ_.front();
	sendPacketQ_.pop_front();

	if (!sendPacketQ_.empty())
	{
		char* pPakcet = sendPacketQ_.front();
		PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(pPakcet);
		PostSend(pHeader);
	}	
}

void Session::HandleRead(boost::system::error_code error_code, std::size_t bytes_transferred)
{
	std::cout << std::this_thread::get_id() << std::endl;	

	std::unique_lock<std::recursive_mutex> guard(mutex_);

	if (error_code)
	{
		if (error_code == boost::asio::error::eof)
		{
			std::cout << error_code.message() << std::endl;
			std::cout << "disconnected client" << std::endl;			
		}
		else
		{
			std::cout << "error id : " << error_code.value() << " error message : " << error_code.message() << std::endl;
		}

		pOwnerServer_->CloseSession(sessionID_);
	}
	else
	{		
		//server can receive the packet more than once at time.	so..It stores the received data in a buffer. And decompose.
		memcpy(&packetBuffer[packetBufferMark_], receiveBuffer_.data(), bytes_transferred);


		size_t packetTotalDataSize = packetBufferMark_ + bytes_transferred;
		int readDataSize = 0;

		while (packetTotalDataSize > 0)
		{
			if (packetTotalDataSize < sizeof(PacketHeader))
			{
				break;
			}
			
			PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(&packetBuffer[readDataSize]);			
			if (pHeader)
			{
				if (pHeader->Size <= packetTotalDataSize)
				{
					pOwnerServer_->ProcessPacket(sessionID_, &packetBuffer[readDataSize]);

					packetTotalDataSize -= pHeader->Size;
					readDataSize += pHeader->Size;
				}
				else
				{
					break;
				}
			}			
		}

		if (packetTotalDataSize > 0)
		{			
			char tempBuff[MAX_RECEIVE_BUFFER_SIZE] = { 0, };
			memcpy(&tempBuff[0], &packetBuffer[readDataSize], packetTotalDataSize);
			memcpy(&packetBuffer[0], &tempBuff[0], packetTotalDataSize);
		}

		packetBufferMark_ = packetTotalDataSize;

		PostReceive();
	}
}
