#pragma once

#include "typedefs.h"

class UMath
{
public:
	static uint CalcRandomSeed();
	static uint GetRandom();
	static void GetRandom(void *ioData, uint inDataSize);
	static constexpr double NormalizeAngle(double x);
	static constexpr double Sine(double x);
	static constexpr double Cosine(double x);
	static constexpr double ArcTangent(double x);
	static constexpr double SquareRoot(double x);
};
