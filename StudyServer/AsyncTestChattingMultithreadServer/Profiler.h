#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

#include "StaticSingleton.h"

class Profiler : public StaticSingleton<Profiler>
{
public:	
	//Profiler(){}
	//~Profiler() {}
	virtual void Initialze() override;
	virtual void Shutdown() override;	

	void SetBegin(std::string checkName);
	void SetEnd(std::string checkName);
	void Report(std::string checkName);

	class ExecutionTimeInfo
	{
	public:
		void Report()
		{
			std::cout << (endTime_ - startTime_).count() << std::endl;
		}

		void SetStart()
		{
			endTime_ = std::chrono::system_clock::now();
		}

		void SetEnd()
		{
			endTime_ = std::chrono::system_clock::now();
		}

	private:
		std::chrono::system_clock::time_point startTime_;
		std::chrono::system_clock::time_point endTime_;
	};

	//typedef std::unordered_map<std::string, ExecutionTimeInfo*> executionTimeMap;	//c++09 style
	using executionTimeMap = std::unordered_map<std::string, ExecutionTimeInfo*>;	//c++11 style

private:			
	executionTimeMap timeProfileMap_;
};

