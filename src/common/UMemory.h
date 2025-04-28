#pragma once

#include "typedefs.h"

#ifdef _WIN32
typedef HGLOBAL TPtr;
#else
typedef void *TPtr;
#endif // _WIN32

/**
 * @brief Memory management class.
 */
class UMemory
{
public:
	/**
	 * @brief Allocates memory of the specified size.
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	static TPtr New(size_t inSize);

	/**
	 * @brief Allocates memory of the specified size and initializes it with the given data.
	 * @param inData Pointer to the data to initialize the memory with.
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	static TPtr New(const void *inData, size_t inSize);

	/**
	 * @brief Allocates memory and clears it.
	 *
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	static TPtr NewClear(size_t inSize);

	/**
	 * @brief Dispose of memory allocated with New.
	 *
	 * @param inPtr Pointer to the memory to dispose of.
	 */
	static void Dispose(TPtr inPtr);

	/**
	 * @brief Reallocate memory to a new size.
	 *
	 * @param inPtr Pointer to the memory to reallocate.
	 * @param inSize New size of the memory.
	 * @return Pointer to the reallocated memory.
	 */
	static TPtr Reallocate(TPtr inPtr, size_t inSize);

	/**
	 * @brief Returns the number of allocations.
	 *
	 * @param outCount Reference to store the allocation count.
	 * @return constexpr longlong
	 */
	static constexpr longlong GetAllocationCount(uint &outCount);

	/**
	 * @brief Fills memory with a byte value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inByte Value to fill the memory with.
	 */
	static void Fill(void *ioDest, uint inSize, byte inByte);

	/**
	 * @brief Fill memory with a word value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inWord Value to fill the memory with.
	 */
	static void Fill(void *ioDest, uint inSize, ushort inWord);

	/**
	 * @brief Fill memory with a long value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inLong Value to fill the memory with.
	 */
	static void Fill(void *ioDest, uint inSize, uint inLong);

	/**
	 * @brief Clears memory with zeroes.
	 *
	 * @param ioDest Pointer to the memory to clear.
	 * @param inSize Size of the memory to clear.
	 */
	static void Clear(void *ioDest, uint inSize);

	/**
	 * @brief Moves memory from one location to another.
	 *
	 * @param ioDest Pointer to the destination memory.
	 * @param inSrc Pointer to the source memory.
	 * @param inSize Size of the memory to move.
	 * @return Number of bytes moved.
	 */
	static uint Move(void *ioDest, const void *inSrc, uint inSize);

	/**
	 * @brief CRC32 checksum calculation
	 *
	 * @param inData Pointer to the data to calculate the checksum for.
	 * @param inDataSize Size of the data.
	 * @param inInit Initial value for the checksum calculation.
	 * @return CRC32 checksum
	 */
	static uint CRC(const void *inData, uint inDataSize, uint inInit);

	/**
	 * @brief Checksum calculation
	 *
	 * @param inData Pointer to the data to calculate the checksum for.
	 * @param inDataSize Size of the data.
	 * @param inInit Initial value for the checksum calculation.
	 * @return Checksum value
	 */
	static uint Checksum(const void *inData, uint inDataSize, uint inInit);

	/**
	 * @brief Search for a block of memory in another block of memory.
	 *
	 * @param inSearchData Pointer to the data to search for.
	 * @param inSearchSize Size of the data to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inDataSize Size of the data to search in.
	 * @return Pointer to the found data, or NULL if not found.
	 */
	static byte *Search(const void *inSearchData, uint inSearchSize, const void *inData,
	                    uint inDataSize);

	/**
	 * @brief Search for a byte in memory.
	 *
	 * @param inByte Byte to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inSize Size of the data to search in.
	 * @return Pointer to the found byte, or NULL if not found.
	 */
	static byte *SearchByte(byte inByte, const void *inData, uint inSize);

	/**
	 * @brief Search for a byte in memory backwards.
	 *
	 * @param inByte Byte to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inDataSize Size of the data to search in.
	 * @return Pointer to the found byte, or NULL if not found.
	 */
	static byte *SearchByteBackwards(byte inByte, const void *inData, uint inDataSize);
};

enum
{
	memError_NotEnough = 0x20065 ///< Not enough memory error code.
};
