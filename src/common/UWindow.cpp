#include "UWindow.h"

#include "typedefs.h"

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#endif // __APPLE__

constexpr unsigned kPaneTag = 0xf0168873;

struct SView
{
	unsigned tag;
#ifdef _WIN32
	HWND hwnd;
#elif defined(__APPLE__)
	CGWindowID macWin;
#else
#endif // _WIN32
};
