#include "TcpServer.h"

#include <istream>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>

#include "Logger.h"
#include "Session.h"


TcpServer::TcpServer(io_service& io_service, unsigned short portNum)
	:acceptor_(io_service, tcp::endpoint(tcp::v4(), portNum))
{
	hasSession = false;
}

void TcpServer::Start()
{
	PostAccept();
}

void TcpServer::Initialize(int maxConnection)
{
	Logger::Log(Logger::LogType::Normal, boost::str(boost::format("Initialize - MaxConnection : %d") % maxConnection));

	sessionList_.clear();

	for (int i = 0; i < maxConnection; ++i)
	{
		Session* pSession = new Session(acceptor_.get_io_service(), i);
		if (pSession)
		{
			sessionList_.push_back(pSession);
			sessionQ_.push(i);
		}
	}
}

bool TcpServer::PostAccept()
{
	if (sessionQ_.empty())
	{		
		Logger::Log(Logger::LogType::Warning, "Max Connection");
		hasSession = false;
		return false;
	}

	hasSession = true;

	int sessionID = sessionQ_.front();	
	sessionQ_.pop();

	acceptor_.async_accept(sessionList_[sessionID]->Socket(),
	boost::bind(&TcpServer::HandleAccept,
		this,
		sessionList_[sessionID],		
		boost::asio::placeholders::error));

	return true;
}

void TcpServer::CloseSession(int sessionID)
{
	//if (sessionList_[sessionID]->Socket().is_open())
	{
		sessionList_[sessionID]->Socket().close();
	}

	sessionQ_.push(sessionID);

	if (!hasSession)
	{
		PostAccept();
	}
}

void TcpServer::HandleAccept(Session* pSession, const boost::system::error_code& error_code)
{
	if (!error_code)
	{		
		Logger::Log(Logger::LogType::Normal, boost::str(boost::format("connected client : sessionID") % pSession->GetSessionID()));		
		
		pSession->Initialze();
		pSession->PostReceive();

		PostAccept();	//continue accept other clients.
	}
	else
	{
		Logger::Log(Logger::LogType::Warning, error_code.message());

		if (!hasSession)
		{
			PostAccept();
		}	
	}
}

TcpServer::~TcpServer()
{
	std::vector<Session*>::iterator it = sessionList_.begin();
	std::vector<Session*>::iterator eit = sessionList_.end();
	for (it; it != eit; ++it)
	{		
		if ((*it) && (*it)->Socket().is_open())
		{
			(*it)->Socket().close();
		}
		delete *it;
		*it = nullptr;
	}
}
