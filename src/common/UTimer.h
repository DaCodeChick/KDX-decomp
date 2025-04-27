#pragma once

#include "MoreTypes.h"

struct STimer;

class UTimer
{
public:
	static STimer *New(TMessageProc inProc, void *inContext);
	static void Dispose(STimer *inRef);
	static void Start(STimer *inRef, uint inMillisecs, uint inIsRepeating);
	static STimer *StartNew(TMessageProc inProc, void *inContext, uint inMillisecs, uint inIsRepeating);
	static void Stop(STimer *inRef);
};
