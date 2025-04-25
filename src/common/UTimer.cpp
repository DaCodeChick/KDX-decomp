#include "UTimer.h"

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
