#include "stdafx.h"
#include "ThreadManager.h"

void ThreadManager::Join()
{
	auto iter = threadHandleList_.begin();
	auto endIter = threadHandleList_.end();
	auto previter = iter;

	
	while (iter != endIter)
	{
		previter = iter++;
		::WaitForSingleObject(*previter, (DWORD)INFINITY);

		threadHandleList_.erase(previter);
	}
}

HANDLE ThreadManager::spawn(LPTHREAD_START_ROUTINE startAddress, LPVOID lpParam, DWORD * idenfier)
{
	auto handle = CreateThread(0, 0, startAddress, lpParam, 0, idenfier);
	threadHandleList_.emplace_back(handle);
	//threadHandleList_.push_back(handle);

	return handle;
}

ThreadManager::~ThreadManager()
{
}