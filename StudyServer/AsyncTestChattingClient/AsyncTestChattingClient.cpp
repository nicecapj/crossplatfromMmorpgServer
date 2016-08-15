// AsyncTestChattingClient.cpp : Defines the entry point for the console application.
//
#include<stdio.h>
#include <iostream>
#include <string>

#include <boost\asio.hpp>
#include <boost/thread.hpp>

#include "Logger.h"
#include "TcpChatClient.h"
#include "../AsyncTestChattingServer/Protocol.h"

int main()
{
	boost::asio::io_service ios;

	std::string SERVER_ADDRESS = "127.0.0.1";
	boost::uint16_t SERVER_PORT = 7777;	

	auto address = boost::asio::ip::address::from_string(SERVER_ADDRESS);
	boost::asio::ip::tcp::endpoint endpoint(address, SERVER_PORT);

	TcpChatClient client(ios, endpoint);
	client.Connect();

	//ios.run();	//do not return.  because of thread block
	boost::thread workThread(boost::bind(&boost::asio::io_service::run, &ios));	

	char messageBuff[MAX_MESSAGE_LENGTH] = { 0, };
	while (std::cin.getline(messageBuff, MAX_MESSAGE_LENGTH))
	{
		if (strlen(messageBuff) == 0)
		{
			break;
		}

		if (!client.IsConnected())
		{
			Logger::Log(Logger::LogType::Error, "disconnected with server");
		}

		if (client.IsLogin())
		{
			PacketChatReq packet;
			strcpy_s(packet.Message, MAX_NICNAME_LENGTH, messageBuff);
			client.PostSend<PacketChatReq>(&packet);
		}
		else
		{
			PacketLoginReq packet;
			strcpy_s(packet.NickName, MAX_NICNAME_LENGTH, messageBuff);
			client.PostSend<PacketLoginReq>(&packet);
		}
	}


	
	ios.stop();
	client.Close();
	workThread.join();

	getchar();
	return 0;
}