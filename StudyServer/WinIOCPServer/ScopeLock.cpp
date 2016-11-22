#include "stdafx.h"
#include "ScopeLock.h"


ScopeLock::ScopeLock(CRITICAL_SECTION* cs)
{
	cs_ = cs;

	EnterCriticalSection(cs_);
}


ScopeLock::~ScopeLock()
{
	LeaveCriticalSection(cs_);
}
