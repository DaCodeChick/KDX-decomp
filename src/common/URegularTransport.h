#pragma once

#include "typedefs.h"

struct SRegularTransport;

typedef void (*TConnectionHandlerProc)(uint inListenPort, SRegularTransport *inTpt, int inType);

class URegularTransport
{
public:
	static void Init();
	static SRegularTransport * New(TConnectionHandlerProc inProc, void *inContext, uint inProtocol, int inMode);
	static void Send(SRegularTransport *inTpt, const void *inData, uint inDataSize);
	static void * Receive(SRegularTransport *inTpt, uint *outMaxSize, bool *outHasMoreData);
	static void LaunchURL(const void *inText, uint inTextSize);
};
