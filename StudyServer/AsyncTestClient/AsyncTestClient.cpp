// AsyncTestClient.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <boost\asio.hpp>
#include <string>
#include "TcpClient.h"

//void HandlerConnect(boost::a)
int main()
{
	boost::asio::io_service ios;

	std::string SERVER_ADDRESS = "127.0.0.1";
	boost::uint16_t SERVER_PORT = 7777;
	
	//boost::asio::ip::s

	auto address = boost::asio::ip::address::from_string(SERVER_ADDRESS);
	boost::asio::ip::tcp::endpoint endpoint(address, SERVER_PORT);
	
	//boost::asio::ip::tcp::socket socket(ios, endpoint);
	//
	//socket.async_connect(endpoint, [](boost::system::error_code errorCode)->void 
	//{ 
	//	std::cout << "";
	//});

	TcpClient client(ios, endpoint);
	client.Connect();

	ios.run();
	
	


    return 0;
}

