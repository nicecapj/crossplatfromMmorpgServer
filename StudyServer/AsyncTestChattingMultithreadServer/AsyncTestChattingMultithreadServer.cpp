// AsyncTestChattingMultithreadServer.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <boost/thread.hpp>
#include <memory>

#include "TcpServer.h"
#include "Logger.h"

int main()
{
	const int PORT_NUMBER = 7777;
	const int MAX_CONNECTION = 20;

	boost::asio::io_service ios;

	TcpServer server(ios, PORT_NUMBER);
	server.Initialize(MAX_CONNECTION);
	server.Start();


	std::vector<boost::thread> threads;

	const int MAX_THREAD = 8;
	for (int i = 0; i < MAX_THREAD; ++i)
	{		
		threads.emplace_back(boost::thread(boost::bind(&boost::asio::io_service::run, &ios)));
	}

	ios.run();

	for (int i = 0; i < MAX_THREAD; ++i)
	{
		threads[i].join();
	}



	Logger::Log(Logger::LogType::Normal, "Exit Server");

	getchar();
	return 0;
}
