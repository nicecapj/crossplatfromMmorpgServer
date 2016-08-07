// ASyncTestServer.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include"TcpServer.h"

int main()
{
	boost::asio::io_service ios;

	TcpServer server(ios);
	ios.run();


	std::cout << "Exit Server" << std::endl;

    return 0;
}

