#pragma once

#include "GrafTypes.h"

class UMouse
{
public:
	static uint GetDoubleClickTime();
	static uint GetImage();
	static void SetImage(uint inID);
	static void GetLocation(SPoint &outLoc);
};
