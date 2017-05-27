#include "stdafx.h"
#include "Thread.h"
#include "ThreadManager.h"


Thread::Thread():isStarted(false)
{
}


Thread::~Thread()
{
	printf("123");
}

void Thread::Begin()
{
	if (isStarted)
		return;

	threadHandle_ = ThreadManager::Get()->spawn(ThreadProc, this, &id);

	isStarted = true;
}

void Thread::Run()
{

}

DWORD Thread::ThreadProc(LPVOID lpParam)
{
	Thread* thread = (Thread*)lpParam;

	if (thread != nullptr)
	{
	}
		thread->Run();

	return 0;
}
