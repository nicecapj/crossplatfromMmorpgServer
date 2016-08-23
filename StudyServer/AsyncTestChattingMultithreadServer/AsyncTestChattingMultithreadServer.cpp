// AsyncTestChattingMultithreadServer.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <thread>
#include <memory>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

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


	std::vector<std::thread> threads;

	unsigned int hardwareThreadCount = std::thread::hardware_concurrency();
	const int MAX_THREAD = hardwareThreadCount * 2;	//good for multithread programming.

	for (int i = 0; i < MAX_THREAD; ++i)
	{		
		threads.emplace_back(std::thread(boost::bind(&boost::asio::io_service::run, &ios)));				
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
