// AsyncTestChattingServer.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "TcpServer.h"
#include "Logger.h"

int main()
{
	const int PORT_NUMBER = 7777;
	const int MAX_CONNECTION = 20;

	boost::asio::io_service ios;
	TcpServer server(ios, PORT_NUMBER);
	server.Initialize(MAX_CONNECTION);
	ios.run();

	Logger::Log(Logger::LogType::Normal, "Exit Server");

	getchar();
	return 0;
}

