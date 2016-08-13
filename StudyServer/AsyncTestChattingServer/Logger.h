#pragma once
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
};

