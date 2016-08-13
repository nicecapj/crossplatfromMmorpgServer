// AsyncTestChattingServer.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "TcpServer.h"
#include "Logger.h"

int main()
{
	boost::asio::io_service ios;
	TcpServer server(ios);
	ios.run();

	Logger::Log(Logger::LogType::Normal, "Exit Server");

	getchar();
	return 0;
}

