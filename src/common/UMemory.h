#pragma once

#include "typedefs.h"

#ifdef _WIN32
	typedef HGLOBAL TPtr;
#else
	typedef void * TPtr;
#endif // _WIN32

class UMemory
{
public:
	static TPtr New(size_t inSize);
	static TPtr New(const void *inData, size_t inSize);
	static TPtr NewClear(size_t inSize);
	static void Dispose(TPtr inPtr);
	static TPtr Reallocate(TPtr inPtr, size_t inSize);
	static constexpr longlong GetAllocationCount(uint &outCount);
	static void Fill(void *ioDest, uint inSize, byte inByte);
	static void Fill(void *ioDest, uint inSize, ushort inWord);
	static void Fill(void *ioDest, uint inSize, uint inLong);
	static void Clear(void *ioDest, uint inSize);
	static uint Move(void *ioDest, const void *inSrc, uint inSize);
	static uint CRC(const void *inData, uint inDataSize, uint inInit);
	static uint Checksum(const void *inData, uint inDataSize, uint inInit);
	static byte * Search(void *inSearchData, uint inSearchSize, void *inData, uint inDataSize);
	static byte * SearchByte(byte inByte, void *inData, uint inSize);
	static byte * SearchByteBackwards(byte inByte, void *inData, uint inDataSize);
};

enum
{
	memError_NotEnough = 0x20065
};
