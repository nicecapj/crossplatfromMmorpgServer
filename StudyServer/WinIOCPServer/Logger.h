#pragma once
#include <stdarg.h>
#include <string>

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
