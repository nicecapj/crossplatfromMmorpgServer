// AsyncTestChattingClient.cpp : Defines the entry point for the console application.
//
#include<stdio.h>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Logger.h"
#include "TcpChatClient.h"
#include "../AsyncTestChattingServer/Protocol.h"

#define STRESS_TEST

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

	
#ifndef STRESS_TEST
	char messageBuff[MAX_MESSAGE_LENGTH] = { 0, };
	while (std::cin.getline(messageBuff, MAX_MESSAGE_LENGTH))
	{
		if (strlen(messageBuff) == 0)
		{
			break;
		}
		
		if (!client.IsConnectedServer())
		{
			Logger::Log(Logger::LogType::Error, "disconnected with server");
			break;
		}

		if (client.IsLoggedin())
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
	
#else		
	while (!client.IsConnectedServer())
	{
		//busy wait until connect to server.
		std::cout << "wait to connect" << std::endl;
	}
		
	char messageBuff[MAX_MESSAGE_LENGTH] = { 0, };

	PacketLoginReq packet;
	strcpy(&messageBuff[0], "abcd");
	strcpy_s(packet.NickName, MAX_NICNAME_LENGTH, messageBuff);
	client.PostSend<PacketLoginReq>(&packet);


	for (int i = 0; i < 10000; ++i)
	{
		std::cout << "call : " << i << std::endl;

		PacketChatReq messagePacket;
		strcpy(&messageBuff[0], "ddddd");
		strcpy_s(messagePacket.Message, MAX_NICNAME_LENGTH, messageBuff);
		client.PostSend<PacketChatReq>(&messagePacket);
	}	
#endif

			
	ios.stop();
	client.Close();	
	workThread.join();

	getchar();
	return 0;
}