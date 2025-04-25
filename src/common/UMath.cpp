#pragma once

#include "UMath.h"

#include "UDigest.h"
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
	_gStateIdx = sum & 63;

	return sum;
}


void __cdecl UMath::GetRandom(void *ioData, uint inDataSize)
{
    if (inDataSize == 0) return;

    uint localBuffer[4];
    uint processedSize = 0;

    while (inDataSize > 0)
	{
        UDigest::MD5_Encode((byte *)_gState, sizeof(_gState), localBuffer);
        uint checksum = UMemory::Checksum(_gState, sizeof(_gState), ~_gState[1]);
        uint xorValue = ~_gState[2];

        for (uint i = 0; i < 64; i += 8)
            xorValue ^= _gState[i] ^ _gState[i + 1] ^ _gState[i + 2] ^ _gState[i + 3] ^
                        _gState[i + 4] ^ _gState[i + 5] ^ _gState[i + 6] ^ _gState[i + 7];

        uint chunkSize = (inDataSize < 32) ? inDataSize : 32;

        UMemory::Move(ioData, localBuffer, chunkSize);
        ioData = (void *)((byte *)ioData + chunkSize);
        inDataSize -= chunkSize;

        if (xorValue & 1)
            _gState[0] = (_gState[0] & 0xFFFFFF00) | (_gState[63] & 0xFF);
        else
            _gState[0] = (_gState[0] & 0xFFFF0000) | (_gState[63] & 0xFFFF);

        uint randomSeed = CalcRandomSeed();
        switch (randomSeed & 3) {
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
                _gState[2] = (_gState[2] >> 31) | (_gState[2] * 2);
                break;
        }
    }
}
