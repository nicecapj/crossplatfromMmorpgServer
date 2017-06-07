#pragma once
#include <stdarg.h>
#include <string>

//todo : change log4cpp or gLog
class Logger
{
public:
	Logger();
	~Logger();

	enum LogType
	{		
		Normal,
		Warning,
		Error,
	};

	static void Log(LogType logType, std::string msg);	
	static void Log(LogType logType, char const* const _Format, ...);
};
