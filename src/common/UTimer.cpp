#include "UTimer.h"

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#ifndef _WIN32
#include <signal.h>
#include <time.h>
#include <unistd.h>
#endif // _WIN32
#endif // __APPLE__

constexpr unsigned kTimerTag = 0x1f0d2b21;

struct STimer
{
	STimer *next;
	unsigned tag;
#ifdef _WIN32
	UINT_PTR winTimer;
#elif defined(__APPLE__)
	dispatch_source_t dispatchTimer;
#else
	itimerspec its;
	timer_t timerID;
	sigevent sev;
#endif // _WIN32
	TTimerProc proc;
	void *procContext;
	bool onceOnly;
};
