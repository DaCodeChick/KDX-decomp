#pragma once

#include "typedefs.h"

class UMath
{
public:
	static uint CalcRandomSeed();
	static uint GetRandom();
	static void GetRandom(void *ioData, uint inDataSize);
	static ulonglong Div64U(ulonglong inNumerator, ulonglong inDenominator);
};
