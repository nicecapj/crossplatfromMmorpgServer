#include "Logger.h"
#include <iostream>

#define EnumToStr(a)    #a
static std::string LogTypeName[]
{
	EnumToStr(Normal),
	EnumToStr(Warning),
	EnumToStr(Error),
};

void Logger::Log(Logger::LogType logType, std::string msg)
{	
	std::cout << "["  << ::LogTypeName[logType] << "]" << msg << std::endl;
}

Logger::Logger()
{
}


Logger::~Logger()
{
}
