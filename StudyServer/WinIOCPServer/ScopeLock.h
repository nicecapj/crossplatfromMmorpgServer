#pragma once
class ScopeLock
{
public:
	ScopeLock(CRITICAL_SECTION* cs);
	~ScopeLock();

private:
	CRITICAL_SECTION* cs_;
};