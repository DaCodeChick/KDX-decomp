#include "UMouse.h"

unsigned UMouse::sCurCursorID = 0;

void UMouse::SetImage(unsigned inID)
{
}

unsigned UMouse::GetDoubleClickTime()
{
#ifdef _WIN32
	return ::GetDoubleClickTime();
#else
	return 0;
#endif
}