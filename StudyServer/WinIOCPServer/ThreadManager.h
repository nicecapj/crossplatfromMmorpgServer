#pragma once
#include <list>
#include "Singleton.h"

class ThreadManager : public Singleton<ThreadManager>
{
public:
	void Join();
	HANDLE spawn(LPTHREAD_START_ROUTINE startAddress, LPVOID lpParam, DWORD* idenfier);

	~ThreadManager();

private:		
	std::list<HANDLE> threadHandleList_;
	typedef std::list<HANDLE>::iterator threadHandleListIter_;
};

