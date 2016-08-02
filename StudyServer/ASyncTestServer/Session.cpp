#include "Session.h"


Session::~Session()
{
	if (socket_.is_open())
	{
		socket_.close();
	}
}


void Session::HandleWrite(boost::system::error_code, std::size_t)
{

}

void Session::HandleRead(boost::system::error_code, std::size_t)
{

}