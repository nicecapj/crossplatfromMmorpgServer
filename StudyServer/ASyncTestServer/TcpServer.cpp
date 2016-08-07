#include "TcpServer.h"
#include "Session.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <istream>

const int PORT_NUMBER = 7777;

TcpServer::TcpServer(io_service& io_service)
	:acceptor_(io_service, tcp::endpoint(tcp::v4(), PORT_NUMBER))
{
	pSession_ = nullptr;

	StarAccept();

}

void TcpServer::StarAccept()
{
	pSession_ = new Session(acceptor_.get_io_service());

	acceptor_.async_accept(pSession_->Socket(), 
		boost::bind(&TcpServer::HandleAccept, this, pSession_, boost::asio::placeholders::error));
}

void TcpServer::HandleAccept(Session* pSession, const boost::system::error_code& error_code)
{
	if (!error_code)
	{
		std::cout << "accept client" << std::endl;

		pSession_->PostReceive();
	}
}

TcpServer::~TcpServer()
{

}
