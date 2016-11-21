#pragma once
class Thread
{
public:
	Thread();
	virtual ~Thread();

	void Begin();
	virtual void Run();

	DWORD GetThreadID() { return id ; }

protected:
	HANDLE threadHandle_ = INVALID_HANDLE_VALUE;

private:
	//static DWORD WINAPI ThreadProc(LPVOID lpParam);
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	BOOL isStarted = FALSE;
	DWORD id = 0;
};

