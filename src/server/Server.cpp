#include "Server.h"

#include "../common/UMath.h"

CMyApplication::CMyApplication()
{
	mClientPort = 10700;
	mSeeds[0] = UMath::GetRandom();
	mSeeds[1] = UMath::GetRandom();
	mSeeds[2] = UMath::GetRandom();
}
