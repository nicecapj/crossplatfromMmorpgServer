// WinIOCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


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
	HANDLE threads[5];
	int threadIndex[5] = { 0, };	
	DWORD threadId = 0;

	for (int i = 0; i < 5; ++i)
	{
		threadIndex[i] = i;

		threads[i] = CreateThread(0, 0, ThreadProc, &threadIndex[i], CREATE_SUSPENDED, &threadId);
		if (threads[i] != INVALID_HANDLE_VALUE)
		{
			printf("ThreadId : %d\n", threadId);
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		ResumeThread(threads[i]);
	}

	for (int i = 0; i < 5; ++i)
	{
		std::cout << "main thread\n" << std::endl;
	}
	
	::WaitForMultipleObjects(5, threads, TRUE, INFINITY);
    return 0;
}

