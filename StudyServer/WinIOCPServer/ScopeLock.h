#pragma once

class ScopeLock
{
public:
	ScopeLock(CRITICAL_SECTION* cs);
	~ScopeLock();
	
	static CRITICAL_SECTION gCS;

private:
	CRITICAL_SECTION* cs_;	
};