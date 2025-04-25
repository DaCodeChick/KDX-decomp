#include "UWindow.h"

struct SPane
{
	uint tag;
#ifdef _WIN32
	HWND hwnd;
#endif // _WIN32
};
