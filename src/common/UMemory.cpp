#include "UMemory.h"

#include "UError.h"
#include <cstring>

#ifndef _WIN32
#include <stdlib.h>
#endif // _WIN32

TPtr UMemory::New(size_t inSize)
{
	if (!inSize)
		__Fail(error_Param);
#ifdef _WIN32
	TPtr p = GlobalAlloc(GMEM_FIXED, inSize);
#else
	TPtr p = malloc(inSize);
#endif // _WIN32
	if (!p)
		__Fail(memError_NotEnough);
	_gAllocationCount++;
	return p;
}

TPtr UMemory::New(const void *inData, size_t inSize)
{
	if (!inSize)
		__Fail(error_Param);
#ifdef _WIN32
	TPtr p = GlobalAlloc(GMEM_FIXED, inSize);
#else
	TPtr p = malloc(inSize);
#endif // _WIN32
	if (!p)
		__Fail(memError_NotEnough);
	Move(p, inData, inSize);
	_gAllocationCount++;
	return p;
}

TPtr UMemory::NewClear(size_t inSize)
{
	if (!inSize)
		__Fail(error_Param);
#ifdef _WIN32
	TPtr p = GlobalAlloc(GMEM_ZEROINIT, inSize);
#else
	TPtr p = malloc(inSize);
#endif // _WIN32
	if (!p)
		__Fail(memError_NotEnough);
	Clear(p, inSize);
	_gAllocationCount++;
	return p;
}

void UMemory::Dispose(TPtr inPtr)
{
	if (!inPtr)
		return;
#ifdef _WIN32
	GlobalFree(inPtr);
#else
	free(inPtr);
#endif // _WIN32
	_gAllocationCount--;
}

TPtr UMemory::Reallocate(TPtr inPtr, size_t inSize)
{
	if (!inPtr)
		if (inSize)
			inPtr = New(inSize);
		else if (!inSize)
			Dispose(inPtr);
		else
		{
#ifdef _WIN32
			inPtr = GlobalReAlloc(inPtr, inSize, GMEM_MOVEABLE);
#else
			inPtr = realloc(inPtr, inSize);
#endif // _WIN32
			if (!inPtr)
				__Fail(memError_NotEnough);
		}
	return inPtr;
}

uint64_t UMemory::GetAllocationCount(unsigned &outCount)
{
	outCount = _gAllocationCount;
	return 0;
}

void UMemory::Clear(void *ioDest, size_t inSize)
{
	if (!ioDest || !inSize)
		return;
	memset(ioDest, 0, inSize);
}

void UMemory::Fill(void *ioDest, size_t inSize, uint8_t inByte)
{
	if (!ioDest || !inSize)
		return;
	memset(ioDest, inByte, inSize);
}

void UMemory::Fill(void *ioDest, size_t inSize, uint16_t inWord)
{
	if (!ioDest || !inSize)
		return;
	for (size_t i = 0; i < inSize; i += sizeof(uint16_t))
		*(uint16_t *)((uint8_t *)ioDest + i) = inWord;
}

void UMemory::Fill(void *ioDest, size_t inSize, uint32_t inLong)
{
	if (!ioDest || !inSize)
		return;
	for (size_t i = 0; i < inSize; i += sizeof(uint32_t))
		*(uint32_t *)((uint8_t *)ioDest + i) = inLong;
}

size_t UMemory::Move(void *ioDest, const void *inSrc, size_t inSize)
{
	if (!ioDest || !inSrc || !inSize)
		return;
	memmove(ioDest, inSrc, inSize);
	return inSize;
}
