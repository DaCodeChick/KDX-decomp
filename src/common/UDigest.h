#pragma once

#include "UMemory.h"

class UDigest
{
public:
	/**
	 * @brief MD5 hash algorithm.
	 *
	 * @param inData Pointer to the data to hash.
	 * @param inDataSize Size of the data in bytes.
	 * @param outDigest Pointer to the buffer where the resulting hash will be stored.
	 */
	static void MD5_Encode(const void *inData, size_t inDataSize, void *outDigest);
};

/// @brief MD5 hash algorithm implementation.
class _MD5
{
public:
	/// @brief Default constructor.
	_MD5()
	{
		Init();
	}

	/**
	 * @brief Update the MD5 hash with new data.
	 *
	 * @param inData Pointer to the data to hash.
	 * @param inDataSize Size of the data in bytes.
	 */
	void Update(const uint8_t *inData, size_t inDataSize);

	/**
	 * @brief Finalize the MD5 hash and store the result in outDigest.
	 *
	 * @param outDigest Pointer to the buffer where the resulting hash will be stored.
	 */
	void Report(void *outDigest);

	/// @brief Initialize the MD5 state.
	void Init();

	/**
	 * @brief Clear the buffer and reset the state
	 *
	 * @param inSize Size of the buffer to clear.
	 */
	void Clear(size_t inSize)
	{
		UMemory::Clear(this, inSize);
	}

private:
	uint32_t mState[4];
	uint32_t mCount[2];
	uint8_t mBuffer[64];
	uint32_t mBufferLength;

	void Transform(const uint8_t *inBlock);
};
