#include "stdafx.h"
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

void Logger::Log(LogType logType, char const* const _Format, ...)
{
	int _Result;
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_Result = _vfprintf_l(stdout, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	std::cout << std::endl;
	//return _Result;		
}

Logger::Logger()
{
}


Logger::~Logger()
{
}