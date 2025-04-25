#pragma once

#include "typedefs.h"
#include "MoreTypes.h"

struct STimer
{
	STimer *next;
	uint tag;
#ifdef _WIN32
	UINT_PTR winTimer;
#endif // _WIN32
	TMessageProc msgProc;
	void *msgProcContext;
	bool onceOnly;
};

class UTimer
{
public:
	static STimer * New(TMessageProc inProc, void *inContext);
	static void Dispose(STimer *inRef);
	static void Start(STimer *inRef, uint inMillisecs, uint inIsRepeating);
	static void Stop(STimer *inRef);
};
