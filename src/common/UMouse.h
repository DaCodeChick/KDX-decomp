#pragma once

#include "GrafTypes.h"

class UMouse
{
public:
	static uint GetDoubleClickTime();
	static constexpr uint GetImage();
	static void SetImage(uint inID);
	static void GetLocation(SPoint &outLoc);
};
