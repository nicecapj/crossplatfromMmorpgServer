// TimerTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <chrono>
#include <future>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
//#include <boost/asio/deadline_timer.hpp>
//#include <boost/asio/system_timer.hpp>

void OnTimer(const boost::system::error_code& error);
void OnTimerRepeat(const boost::system::error_code& error, boost::asio::steady_timer* pTimer, std::chrono::microseconds tickMs);
void SetTime(boost::asio::steady_timer* pTimer, std::chrono::microseconds tickMs);

void OnTimer(const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "call timer" << std::endl;
	}
	else
	{
		std::cout << error.value() << " : " << error.message() << std::endl;
	}
}

void SetTime(boost::asio::steady_timer* pTimer, std::chrono::microseconds tickMs)
{
	pTimer->expires_from_now(tickMs);
	pTimer->async_wait(boost::bind(OnTimerRepeat, boost::asio::placeholders::error, pTimer, tickMs));
}

void OnTimerRepeat(const boost::system::error_code& error, boost::asio::steady_timer* pTimer, std::chrono::microseconds tickMs)
{
	if (!error)
	{
		std::cout << "call repeat timer" << std::endl;
		SetTime(pTimer, tickMs);
	}
	else
	{
		std::cout << error.value() << " : " << error.message() << std::endl;
	}
}

int main()
{
	boost::asio::io_service ios;	
	
	boost::asio::steady_timer timer(ios);		
	timer.expires_from_now(std::chrono::milliseconds(1000));
	timer.async_wait(OnTimer);

	boost::asio::steady_timer tick_2000_timer(ios);
	::SetTime(&tick_2000_timer, std::chrono::milliseconds(2000));
	
	ios.run();

	
    return 0;
}

