#pragma once
#include <list>

class ThreadManager
{
public:

	static ThreadManager* GetInstance() 
	{
		//if (instance_ == nullptr)
		//	instance_ = new ThreadManager();
		//
		//return instance_;
		return &instance_;
	}

	void Join();
	HANDLE spawn(LPTHREAD_START_ROUTINE startAddress, LPVOID lpParam, DWORD* idenfier);

private:
	ThreadManager();
	virtual ~ThreadManager();

	static ThreadManager instance_;
	//static ThreadManager* instance_;

	std::list<HANDLE> threadHandleList_;
	typedef std::list<HANDLE>::iterator threadHandleListIter_;
};

