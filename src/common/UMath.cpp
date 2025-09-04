#pragma once

#include "UMath.h"

#include "UDigest.h"
#include "UMemory.h"

#ifndef _WIN32
#include <sys/time.h>
#endif // _WIN32

static unsigned _gRandomSeed = 0;
static unsigned _gState[64] = {0};
static uint8_t _gStateIdx = 0;

unsigned UMath::CalcRandomSeed()
{
#ifdef _WIN32
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return ft.dwLowDateTime;
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec;
#endif // _WIN32
}

unsigned UMath::GetRandom()
{
	auto seed = CalcRandomSeed();
	auto sum = UMemory::Checksum(&_gState, sizeof _gState, seed);

	if (!_gRandomSeed)
		_gRandomSeed = seed;
	_gRandomSeed = _gRandomSeed * 1103515245 + 12345;
	sum ^= _gRandomSeed;
	_gState[_gStateIdx] ^= sum;
	_gStateIdx = sum & 63;

	return sum;
}

unsigned UMath::GetRandom(unsigned &inInit, unsigned inMin, unsigned inMax)
{
	if (inMax < inMin)
		return 0;

	inInit = inInit * 1103515245 + 12345;
	return inMin + inInit % (inMax - inMin + 1);
}

void UMath::GetRandom(void *ioData, size_t inDataSize)
{
	if (!inDataSize)
		return;

	unsigned localBuffer[4];
	auto processedSize = 0;

	while (inDataSize > 0)
	{
		UDigest::MD5_Encode((byte *)_gState, sizeof(_gState), localBuffer);
		auto checksum = UMemory::Checksum(_gState, sizeof(_gState), ~_gState[1]);
		auto xorValue = ~_gState[2];

		for (auto i = 0; i < 64; i += 8)
			xorValue ^= _gState[i] ^ _gState[i + 1] ^ _gState[i + 2] ^ _gState[i + 3] ^
			            _gState[i + 4] ^ _gState[i + 5] ^ _gState[i + 6] ^ _gState[i + 7];

		auto chunkSize = (inDataSize < 32) ? inDataSize : 32;

		UMemory::Move(ioData, localBuffer, chunkSize);
		ioData = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(ioData) + chunkSize);
		inDataSize -= chunkSize;

		if (xorValue & 1)
			_gState[0] = (_gState[0] & 0xFFFFFF00) | (_gState[63] & 0xFF);
		else
			_gState[0] = (_gState[0] & 0xFFFF0000) | (_gState[63] & 0xFFFF);

		auto randomSeed = CalcRandomSeed();
		switch (randomSeed & 3)
		{
			case 0:
				_gState[1] = (_gState[1] << 28) | (_gState[1] >> 4);
				_gState[3] = ((_gState[3] << 29) | (_gState[3] >> 3)) + 1;
				break;
			case 1:
				_gState[6] = (_gState[6] << 31) | (_gState[6] >> 1);
				break;
			case 2:
				_gState[0] = (_gState[0] << 31) | (_gState[0] >> 1);
				break;
			default:
				_gState[2] = (_gState[2] >> 31) | (_gState[2] << 1);
				break;
		}
	}
}
