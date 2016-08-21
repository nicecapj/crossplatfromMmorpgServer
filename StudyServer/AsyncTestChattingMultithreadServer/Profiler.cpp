#include "Profiler.h"
#include <utility>



void Profiler::Initialze()
{
	std::cout << "123123" << std::endl;
}

void Profiler::Shutdown()
{
	auto it = timeProfileMap_.begin();
	auto eit = timeProfileMap_.end();
	for (it; it != eit; ++it)
	{
		delete it->second;
	}

	timeProfileMap_.clear();
}


void Profiler::SetBegin(std::string checkName)
{	
	auto iter = timeProfileMap_.find(checkName);
	if (iter != timeProfileMap_.end())
	{
		if (iter->second)
		{
			iter->second->SetStart();
		}		
	}
	else
	{
		ExecutionTimeInfo* timeInfo = new ExecutionTimeInfo();
		if (timeInfo)
		{
			timeInfo->SetStart();
			timeProfileMap_.insert(executionTimeMap::value_type(checkName, timeInfo));			
		}		
	}
}

void Profiler::SetEnd(std::string checkName)
{
	auto iter = timeProfileMap_.find(checkName);
	if (iter != timeProfileMap_.end())
	{
		if (iter->second)
		{
			iter->second->SetEnd();
		}
	}
}

void Profiler::Report(std::string checkName)
{
	auto iter = timeProfileMap_.find(checkName);
	if (iter != timeProfileMap_.end())
	{
		if (iter->second)
		{
			iter->second->Report();
		}
	}
}