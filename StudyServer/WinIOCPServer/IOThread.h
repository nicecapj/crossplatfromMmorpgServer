#pragma once
#include "Thread.h"

class IOThread : public Thread
{
public:
	IOThread(HANDLE iocpHandle) 
		:iocpHandle_(iocpHandle) 
	{}
	IOThread() {}
	void SetIOCPHandle(HANDLE iocpHandle)
	{
		iocpHandle_ = iocpHandle;
	}

	virtual void Run();

	HANDLE iocpHandle_;
};
