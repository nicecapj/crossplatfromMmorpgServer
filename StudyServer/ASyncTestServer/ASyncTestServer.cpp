// ASyncTestServer.cpp : Defines the entry point for the console application.
//
#include<stdio.h>
#include<iostream>
#include"TcpServer.h"

int main()
{
	boost::asio::io_service ios;

	TcpServer server(ios);
	ios.run();


	std::cout << "Exit Server" << std::endl;

	getchar();
    return 0;
}

