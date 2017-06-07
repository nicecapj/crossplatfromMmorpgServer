#include "stdafx.h"
#include "LogicThread.h"
#include <math.h>
#include <assert.h>
#include "Logger.h"

void LogicThread::Run()
{
	while (1)
	{
		Thread::Run();
		//Logger::Log(Logger::Normal, "LogicThread");
	}
}
