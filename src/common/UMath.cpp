#pragma once

#include "UMath.h"

#include "UMemory.h"

static uint _gRandomSeed = 0;
static uint _gState[64] = { 0 };
static byte _gStateIdx = 0;

uint UMath::CalcRandomSeed()
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return ft.dwLowDateTime;
}

uint UMath::GetRandom()
{
	uint seed = CalcRandomSeed();
	uint sum = UMemory::Checksum(&_gState, sizeof _gState, seed);
	
	if (!_gRandomSeed) _gRandomSeed = seed;
	_gRandomSeed = _gRandomSeed * 1103515245 + 12345;
	sum ^= _gRandomSeed;
	_gState[_gStateIdx] ^= sum;
	_gStateIdx = sum & 0x3F;

	return sum;
}