// SyncTestServer.cpp : Defines the entry point for the console application.
//
// sync echo server
#include <iostream>
#include <string>
#include "boost/asio.hpp"


using boost::asio::ip::tcp;
const std::string SERVER_IP = "127.0.0.1";
const unsigned short SERVER_PORT = 7777;

int main()
{
	boost::asio::io_service ios;
	tcp::endpoint endpoint(tcp::v4(), SERVER_PORT);
	
	//old listen flow
	tcp::acceptor acceptor(ios);
	acceptor.open(endpoint.protocol());
	acceptor.set_option(boost::asio::socket_base::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen();

	//tcp::acceptor acceptor(ios, endpoint);	//new listen flow


	tcp::socket socket(ios);
	acceptor.accept(socket);

	std::cout << "connected Client" << std::endl;

	
	for (;;)
	{
		std::array<char, 128> buff;
		buff.assign(0);

		boost::system::error_code error;
		size_t len = socket.read_some(boost::asio::buffer(buff), error);

		if (error)
		{

			if (error == boost::asio::error::eof)
			{
				std::cout << error.message() << std::endl;
				std::cout << "disconnected client" << std::endl;
			}					
			else
			{
				std::cout << "error id : " << error.value() << " error message : " << error.message() << std::endl;
			}
		}

		std::cout << "Msg : " << &buff[0] << std::endl;

		boost::system::error_code write_error;
		std::string tempStringbuffer;
		socket.write_some(boost::asio::buffer(tempStringbuffer), write_error);

				
		char szMessage[128] = { 0, };
		//sprintf_s(szMessage, 128 - 1, "Request : %s", &buff[0]);
		sprintf_s(szMessage, 128 - 1, "Request : %s", buff.data());
		size_t msgCount = strnlen_s(szMessage, 128 - 1);

		socket.write_some(boost::asio::buffer(szMessage, msgCount), write_error);
	}

    return 0;
}

