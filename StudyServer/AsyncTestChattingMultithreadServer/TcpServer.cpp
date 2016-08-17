#include "TcpServer.h"

#include <istream>

#include <boost/bind.hpp>
#include <boost/function.hpp>
//#include <boost/format.hpp>

#include "Protocol.h"
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
	//Logger::Log(Logger::LogType::Normal, boost::str(boost::format("Initialize - MaxConnection : %d") % maxConnection));
	Logger::Log(Logger::LogType::Normal, "Initialize - MaxConnection : %d", maxConnection);

	sessionList_.clear();

	for (int i = 0; i < maxConnection; ++i)
	{
		Session* pSession = new Session(acceptor_.get_io_service(), i, this);
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

void TcpServer::ProcessPacket(const int sessionID, const char* pReceivedPacket)
{
	//PACKET_HEADER* pHeader = reinterpret_cast<PACKET_HEADER*>(pPacketData);
	PacketHeader* pHeader = (PacketHeader*)(pReceivedPacket);

	Session* pCurrentSession = sessionList_[sessionID];


	switch (pHeader->Id)
	{		
		case PacketCode::LoginReq:
		{
			const PacketLoginReq* pPacket = reinterpret_cast<const PacketLoginReq*>(pReceivedPacket);
			if (pPacket)
			{
				pPacket->Id;				

				sessionList_[sessionID]->SetName(pPacket->NickName);
				Logger::Log(Logger::LogType::Normal, "Client login : %s\n", pPacket->NickName);

				PacketLoginRes resPacket;
				resPacket.isSuccess = true;
				
				pCurrentSession->PostSend(&resPacket);
			}
		}
		break;

		case PacketCode::ChatReq:
		{
			const PacketChatReq* pPacket = reinterpret_cast<const PacketChatReq*>(pReceivedPacket);
			if (pPacket)
			{
				PacketChatRes resPacket;
				resPacket.isSuccess = true;
				resPacket.Set(pCurrentSession->GetName(), pPacket->Message);//if client save data, not necessary
				pCurrentSession->PostSend(&resPacket);
				
				if (resPacket.isSuccess == true)
				{
					for (auto session : sessionList_)
					{
						if (session->GetSessionID() == sessionID)
							continue;

						if (session->Socket().is_open())
						{
							PacketChatNfy broadcastPacket;
							broadcastPacket.Set(pCurrentSession->GetName(), pPacket->Message);
							session->PostSend(&broadcastPacket);
						}
					}
				}				
			}
		}
		break;
		
		//client
		//case PacketCode::EnterRes: 
		//{
		//	const PacketEnterRes* pPacket = reinterpret_cast<const PacketEnterRes*>(pReceivedPacket);
		//	if (pPacket->isSuccess)
		//	{

		//	}
		//}
		//break;
		//
		//case PacketCode::ChatRes: 
		//{
		//	const PacketChatRes* pPacket = reinterpret_cast<const PacketChatRes*>(pReceivedPacket);			
		//	std::cout << pPacket->NickName << " : " << pPacket->Message << std::endl;
		//}
		//break;
	}
}

void TcpServer::HandleAccept(Session* pSession, const boost::system::error_code& error_code)
{
	if (!error_code)
	{		
		//Logger::Log(Logger::LogType::Normal, boost::str(boost::format("connected client : sessionID") % pSession->GetSessionID()));		
		Logger::Log(Logger::LogType::Normal, "connected client : sessionID : %d", pSession->GetSessionID());
		
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
