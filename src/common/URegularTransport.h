#pragma once

#include "CPtrList.h"
#include "MoreTypes.h"

struct SSendBuf
{
	SSendBuf *next;
	byte *data;
	uint dataSize;
};

struct SRegularTransport
{
	SRegularTransport *next;
	uint tag; // 0x42781ea5
#ifdef _WIN32
	SOCKET sock;
	HWND hwnd;
#endif // _WIN32
	int id;
	TMessageProc msgProc;
	void *msgProcContext;
#ifdef _WIN32
	HANDLE asyncTaskHandle;
#endif // _WIN32
	int errorCode;
	CPtrList<SSendBuf> sendQueue;
	uint bytesSent;
	byte status;
	bool writePending;
	bool isShuttingDown;
	bool isClosed;
	bool isTemp;
};

typedef void (*TConnectionHandlerProc)(uint inListenPort, SRegularTransport *inTpt, int inType);

class URegularTransport
{
public:
	static void Init();
	static SRegularTransport * New(TConnectionHandlerProc inProc, void *inContext, uint inProtocol, int inMode);
};
