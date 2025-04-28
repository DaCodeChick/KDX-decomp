#pragma once

#include "typedefs.h"

class UDigest
{
public:
	static void MD5_Encode(const void *inData, uint inDataSize, void *outDigest);
	static void AugmentedMD5_Encode(const void *inData, uint inDataSize, void *outDigest);
};

/// @brief MD5 hash algorithm implementation.
class _MD5
{
public:
	/// @brief Default constructor.
	_MD5();

	/**
	 * @brief Update the MD5 hash with new data.
	 *
	 * @param inData Pointer to the data to hash.
	 * @param inDataSize Size of the data in bytes.
	 */
	void Update(const byte *inData, uint inDataSize);

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
	void Clear(uint inSize);

private:
	uint mState[4];
	uint mCount[2];
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const byte *inBlock);
};
