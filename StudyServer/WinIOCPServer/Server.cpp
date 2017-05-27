// WinIOCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Thread.h"
#include "IOCPServer.h"
#include "WS32SocketServer.h"

HANDLE g_IOCP;

class IOThread : public Thread
{
public:
	virtual void Run()
	{
		//Thread::Run();
		while (1)
		{
			//std::cout << "IOThread : " << this->GetThreadID() << std::endl;

			DWORD transferred = 0;
			LONG completeKey = 1;
			LPOVERLAPPED data;
			if (GetQueuedCompletionStatus(g_IOCP, &transferred, (PULONG_PTR)&completeKey, &data, (DWORD)INFINITY))
			{

			}
			else
			{
				std::cout << "IOThread : " << this->GetThreadID() << std::endl;
			}
		}		
	}
};

DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
	int* threadId = (int*)lpParameter;

	std::cout << *threadId << std::endl;

	while(1)
	//for (;;)
	{
		printf("thread : %d\n", *threadId);
	}
	
	return 0;
}




int main()
{		
	//todo : set crash handler
	//todo : client manager
	//todo : create db manager
	//----------------------------------------------------------------------------------------------------------
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	printf("CPU Count : %d", sysInfo.dwNumberOfProcessors);
	
	int kvp = 1;
	g_IOCP = CreateIoCompletionPort(0, 0, (ULONG_PTR)&kvp, sysInfo.dwNumberOfProcessors);
	//network server
	IOCPServer server;
	if (g_IOCP != INVALID_HANDLE_VALUE)
	{		
		server.Initialize(g_IOCP, 4444);
	}

	//io
	IOThread ioThread[5];
	for (int i = 0; i < 5; ++i)
	{
		ioThread[i].Begin();
	}
	
	while (1)
	{
		server.OnTick();
	}
	//----------------------------------------------------------------------------------------------------------
	////logic
	//HANDLE threads[5];
	//int threadIndex[5] = { 0, };
	//DWORD threadId = 0;

	//for (int i = 0; i < 5; ++i)
	//{
	//	threadIndex[i] = i;

	//	threads[i] = CreateThread(0, 0, ThreadProc, &threadIndex[i], CREATE_SUSPENDED, &threadId);
	//	if (threads[i] != INVALID_HANDLE_VALUE)
	//	{
	//		printf("ThreadId : %d\n", threadId);
	//	}
	//}

	//for (int i = 0; i < 5; ++i)
	//{
	//	ResumeThread(threads[i]);
	//}

	//for (int i = 0; i < 5; ++i)
	//{
	//	std::cout << "main thread\n" << std::endl;
	//}

	//::WaitForMultipleObjects(5, threads, TRUE, (DWORD)INFINITY);
	//----------------------------------------------------------------------------------------------------------


	getchar();

    return 0;
}

