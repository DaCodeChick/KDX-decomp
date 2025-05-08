#pragma once

#include "typedefs.h"

#include <cstring>

#ifdef _WIN32
typedef HGLOBAL TPtr;
#else
typedef void *TPtr;
#endif // _WIN32

/// @brief Memory management class.
class UMemory
{
public:
	/**
	 * @brief Allocates memory of the specified size.
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	[[nodiscard]] static TPtr New(size_t inSize);

	/**
	 * @brief Allocates memory of the specified size and initializes it with the given data.
	 * @param inData Pointer to the data to initialize the memory with.
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	[[nodiscard]] static TPtr New(const void *inData, size_t inSize);

	/**
	 * @brief Allocates memory and clears it.
	 *
	 * @param inSize Size of memory to allocate.
	 * @return Pointer to allocated memory.
	 */
	[[nodiscard]] static TPtr NewClear(size_t inSize);

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
	[[nodiscard]] static TPtr Reallocate(TPtr inPtr, size_t inSize);

	/**
	 * @brief Fill memory with a word value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inWord Value to fill the memory with.
	 */
	static void Fill(void *ioDest, size_t inSize, uint16_t inWord);

	/**
	 * @brief Fill memory with a long value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inLong Value to fill the memory with.
	 */
	static void Fill(void *ioDest, size_t inSize, uint32_t inLong);

	/**
	 * @brief Clears memory with zeroes.
	 *
	 * @param ioDest Pointer to the memory to clear.
	 * @param inSize Size of the memory to clear.
	 */
	static void Clear(void *ioDest, size_t inSize)
	{
		if (ioDest && inSize)
			std::memset(ioDest, 0, inSize);
	}

	/**
	 * @brief Returns the number of allocations.
	 *
	 * @param outCount Reference to store the allocation count.
	 * @return 0
	 */
	static uint64_t GetAllocationCount(unsigned &outCount)
	{
		outCount = sAllocationCount;
		return 0;
	}

	/**
	 * @brief Moves memory from one location to another.
	 *
	 * @param ioDest Pointer to the destination memory.
	 * @param inSrc Pointer to the source memory.
	 * @param inSize Size of the memory to move.
	 * @return Number of bytes moved.
	 */
	static size_t Move(void *ioDest, const void *inSrc, size_t inSize)
	{
		if (!ioDest || !inSrc || !inSize)
			return 0;
		std::memmove(ioDest, inSrc, inSize);
		return inSize;
	}

	/**
	 * @brief Fills memory with a byte value.
	 *
	 * @param ioDest Pointer to the memory to fill.
	 * @param inSize Size of the memory to fill.
	 * @param inByte Value to fill the memory with.
	 */
	static void Fill(void *ioDest, size_t inSize, uint8_t inByte)
	{
		if (ioDest && inSize)
			std::memset(ioDest, inByte, inSize);
	}

	/**
	 * @brief Search for a block of memory in another block of memory.
	 *
	 * @param inSearchData Pointer to the data to search for.
	 * @param inSearchSize Size of the data to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inDataSize Size of the data to search in.
	 * @return Pointer to the found data, or NULL if not found.
	 */
	[[nodiscard]] static constexpr const void *Search(const void *inSearchData, size_t inSearchSize,
	                                                  const void *inData, size_t inDataSize)
	{
		if (!inSearchData || !inData || !inSearchSize || !inDataSize || inSearchSize > inDataSize)
			return NULL;

		auto searchData = reinterpret_cast<const uint8_t *>(inSearchData);
		auto data = reinterpret_cast<const uint8_t *>(inData);

		// Special case for single-byte search
		if (inSearchSize == 1)
			return reinterpret_cast<const void *>(SearchByte(*searchData, inData, inDataSize));

		// Precompute the bad character shift table
		int badCharShift[256] = {0};
		for (auto i = 0; i < 256; ++i)
			badCharShift[i] = inSearchSize;

		for (auto i = 0; i < inSearchSize - 1; ++i)
			badCharShift[searchData[i]] = inSearchSize - 1 - i;

		auto offset = 0;
		while (offset <= inDataSize - inSearchSize)
		{
			auto i = inSearchSize - 1;

			// Compare the pattern from the end
			while (i >= 0 && searchData[i] == data[offset + i])
				--i;

			if (i < 0)
				return static_cast<const void *>(data + offset);

			// Shift based on the bad character rule
			offset += badCharShift[data[offset + inSearchSize - 1]];
		}

		return NULL;
	}

	/**
	 * @brief Search for a byte in memory.
	 *
	 * @param inByte Byte to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inSize Size of the data to search in.
	 * @return Pointer to the found byte, or NULL if not found.
	 */
	[[nodiscard]] static constexpr const uint8_t *SearchByte(uint8_t inByte, const void *inData,
	                                                         size_t inSize)
	{
		if (!inData || !inSize)
			return NULL;

		auto dataPtr = reinterpret_cast<const uint8_t *>(inData);

		for (auto i = 0; i < inSize; ++i)
			if (dataPtr[i] == inByte)
				return &dataPtr[i];

		return NULL;
	}

	/**
	 * @brief Search for a byte in memory backwards.
	 *
	 * @param inByte Byte to search for.
	 * @param inData Pointer to the data to search in.
	 * @param inDataSize Size of the data to search in.
	 * @return Pointer to the found byte, or NULL if not found.
	 */
	[[nodiscard]] static constexpr const uint8_t *
	SearchByteBackwards(byte inByte, const void *inData, size_t inDataSize)
	{
		if (!inData || !inDataSize)
			return NULL;

		auto dataPtr = reinterpret_cast<const uint8_t *>(inData);

		for (auto i = inDataSize - 1; i >= 0; --i)
			if (dataPtr[i] == inByte)
				return &dataPtr[i];

		return NULL;
	}

	/**
	 * @brief Checksum calculation
	 *
	 * @param inData Pointer to the data to calculate the checksum for.
	 * @param inDataSize Size of the data.
	 * @param inInit Initial value for the checksum calculation.
	 * @return Checksum value
	 */
	[[nodiscard]] static uint32_t Checksum(const void *inData, size_t inDataSize, uint32_t inInit);

	/**
	 * @brief CRC32 checksum calculation
	 *
	 * @param inData Pointer to the data to calculate the checksum for.
	 * @param inDataSize Size of the data.
	 * @param inInit Initial value for the checksum calculation.
	 * @return CRC32 checksum
	 */
	[[nodiscard]] static uint32_t CRC(const void *inData, size_t inDataSize, uint32_t inInit);

	/**
	 * @brief Adler-32 checksum calculation
	 *
	 * @param inData Pointer to the data to calculate the checksum for.
	 * @param inDataSize Size of the data.
	 * @param inInit Initial value for the checksum calculation.
	 * @return Adler-32 checksum
	 */
	[[nodiscard]] static uint32_t AdlerSum(const void *inData, size_t inDataSize, uint32_t inInit);

private:
	static unsigned sAllocationCount;
};

enum
{
	memError_NotEnough = 0x20065 ///< Not enough memory error code.
};
