#include "Session.h"
#include <string>

#include "TcpServer.h"
#include "Logger.h"

Session::Session(boost::asio::io_service& ios, int sessionID, TcpServer* pOwnerServer)
	:socket_(ios), pOwnerServer_(pOwnerServer)
{
	sessionID_ = sessionID;	
}

Session::~Session()
{
	if (socket_.is_open())
	{
		socket_.close();
	}
}

void Session::Initialze()
{

}

void Session::PostReceive()
{
	memset(receiveBuffer_.data(), 0, receiveBuffer_.size());

	socket_.async_read_some(boost::asio::buffer(receiveBuffer_),
		boost::bind(&Session::HandleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));	
}

void Session::PostSend()
{
}

void Session::HandleWrite(boost::system::error_code error_code, std::size_t bytes_transferred)
{

}

void Session::HandleRead(boost::system::error_code error_code, std::size_t bytes_transferred)
{	
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
		const std::string strRecvMessage = receiveBuffer_.data();
		std::cout << "recv message : " << strRecvMessage << "size : " << bytes_transferred << std::endl;

		char szMessage[128] = { 0 };
		sprintf_s(szMessage, 128 - 1, "Re : %s", strRecvMessage.c_str());
		writeMessage = szMessage;

		boost::asio::async_write(socket_, boost::asio::buffer(writeMessage),
			[this](boost::system::error_code error_code, std::size_t bytes_transfered)-> void
		{
			HandleWrite(error_code, bytes_transfered);
		});

		PostReceive();
	}
}