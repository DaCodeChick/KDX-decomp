#include "UFileSys.h"

struct SFileSysRef
{
#ifdef _WIN32
	HANDLE h;
#else
	int h;
#endif        // _WIN32
	uint tag; // 0x1ca6c39a
	wchar_t *path;
	uint pathSize;
	uint pathFlags;
	uint flags;
};
