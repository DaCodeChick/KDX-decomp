#include "URegularTransport.h"

#include "CPtrList.h"
#include "MoreTypes.h"
#include "UError.h"
#include "UMessageSys.h"

#ifndef _WIN32
#endif // _WIN32

static bool _gIsInitialized = false;

#ifdef _WIN32
static ATOM _TRSockClassAtom = 0;
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
#else  // _WIN32
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

#ifdef _WIN32
static LRESULT CALLBACK _TRSockProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
#endif // _WIN32

static void _Deinit()
{
#ifdef _WIN32
	WSACleanup();
#endif // _WIN32
}

void URegularTransport::Init()
{
	if (_gIsInitialized)
		return;

	UMessageSys::Init();
#ifdef _WIN32
	WNDCLASSEXA wc;

	wc.hInstance = GetModuleHandleA(NULL);
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = 0;
	wc.lpfnWndProc = _TRSockProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "%%stdwinsockclass%%";
	wc.hIconSm = NULL;

	_TRSockClassAtom = RegisterClassExA(&wc);
	if (!_TRSockClassAtom)
		;

	int err = WSAStartup(MAKEWORD(2, 2), NULL);
	if (err)
		_FailWinError(err);
#endif // _WIN32
	_gIsInitialized = true;
}
