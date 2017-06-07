#include "stdafx.h"
#include "IOThread.h"
#include <math.h>
#include <assert.h>

void IOThread::Run()
{
	assert(iocpHandle_ != INVALID_HANDLE_VALUE);
	if (iocpHandle_ == INVALID_HANDLE_VALUE)
		return;
	
	while (1)
	{
		Thread::Run();
		//std::cout << "IOThread : " << this->GetThreadID() << std::endl;

		DWORD transferred = 0;
		LONG completeKey = 1;
		LPOVERLAPPED data;
		if (GetQueuedCompletionStatus(iocpHandle_, &transferred, (PULONG_PTR)&completeKey, &data, (DWORD)INFINITY))
		{

		}
		else
		{
			//std::cout << "IOThread : " << this->GetThreadID() << std::endl;
		}
	}
}
