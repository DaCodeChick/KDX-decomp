#pragma once

#include "typedefs.h"

class UMath
{
public:
	static uint CalcRandomSeed();
	static uint GetRandom();
	static void GetRandom(void *ioData, uint inDataSize);
	static double NormalizeAngle(double x);
	static double Sine(double x);
	static double Cosine(double x);
	static double ArcTangent(double x);
	static double SquareRoot(double x);
	static double GetPi();
};
