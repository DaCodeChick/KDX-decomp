#include "UFileSys.h"

constexpr unsigned kFileSysRefTag = 0x1ca6c39a;

struct SFileSysRef
{
#ifdef _WIN32
	HANDLE h;
#else
	int h;
#endif // _WIN32
	unsigned tag;
	wchar_t *path;
	size_t pathSize;
	unsigned pathFlags;
	unsigned flags;
};
