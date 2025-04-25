#pragma once

#include "typedefs.h"

class UText
{
public:
	static void Format(void *outText, uint inMaxSize, const char *inFormat, ...);
	static uint IntegerToText(uint inInteger, void *outText, uint inMaxSize, uint inOptions);
	static uint TextToInteger(const void *inText, uint inTextSize, uint inOptions);
	static void ToLower(const void *inText, uint inTextSize, void *outText, uint inMaxSize);
};
