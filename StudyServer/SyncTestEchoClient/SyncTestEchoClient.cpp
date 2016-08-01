// SyncTestEchoClient.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

const std::string SERVER_IP = "127.0.0.1";
const unsigned short SERVER_PORT = 7777;

int main()
{	
	boost::asio::io_service ios;
			
	tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_PORT);	
	tcp::socket socket(ios);

	boost::system::error_code error_code;
	socket.connect(endpoint, error_code);

	if (error_code)
	{
		std::cout << "failed to connect : " << error_code.message() << error_code.value() << std::endl;
		//10061 : 서버 안 떠있어서 접속 안되는 경우 경우 : 대상 컴퓨터에서 연결을 거부했음으로 연결하지 못했습니다		
		getchar();
	}
	else
	{
		std::cout << "succed to connect" << std::endl;
	}

		
	for (;;)
	{
		std::string msg;
		std::cin >> msg;

		socket.write_some(boost::asio::buffer(msg), error_code);
		if (error_code)
		{
			if (error_code == boost::asio::error::eof)
			{
				std::cout << error_code.message() << std::endl;
				std::cout << "disconnected" << std::endl;
				//10054 : 소켓이 연결되었어도, 서버가 종룐나 다운된경우, 
				//r/w를 할수 없어서 " 현재 연결은 원격 호스트에 의해 강제로 끊겼습니다. 메시지를 보게됨"
			}
			else
			{
				std::cout << "msg id : " << error_code.value() << " error message : " << error_code.message() << std::endl;
			}
		}
		
		std::array<char, 128> readBuff;
		readBuff.assign(0);		
		socket.read_some(boost::asio::buffer(readBuff), error_code);

		if (error_code)
		{
			if (error_code == boost::asio::error::eof)
			{
				std::cout << error_code.message() << std::endl;
				std::cout << "disconnected" << std::endl;
			}
			else
			{
				std::cout << "msg id : " << error_code.value() << " error message : " << error_code.message() << std::endl;
			}
		}

		std::cout << "Msg : " << readBuff.data() << std::endl;;


		if (socket.is_open())
		{
			socket.close();
		}

	}
    return 0;
}

