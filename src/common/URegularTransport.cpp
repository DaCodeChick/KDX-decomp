#include "URegularTransport.h"

#include "CPtrList.h"
#include "MoreTypes.h"

#ifdef _WIN32
#include <winsock.h>
#else // _WIN32
#endif // _WIN32

constexpr unsigned kRegularTransportTag = 0x42781ea5;

struct SSendBuf
{
	SSendBuf *next;
	uint8_t *data;
	size_t dataSize;
};

struct SRegularTransport
{
	SRegularTransport *next;
	unsigned tag;
#ifdef _WIN32
	SOCKET sock;
	HWND hwnd;
#else // _WIN32
	int sock;
#endif // _WIN32
	int id;
	TMessageProc msgProc;
	void *msgProcContext;
#ifdef _WIN32
#endif // _WIN32
	int errorCode;
	CPtrList<SSendBuf> sendQueue;
	size_t bytesSent;
	uint8_t status;
	bool writePending;
	bool isShuttingDown;
	bool isClosed;
	bool isTemp;
};
