#pragma once

#include "typedefs.h"

/// @brief Twofish cipher class
class HXAPI CTwofish
{
public:
	/**
	 * @brief Constructor
	 *
	 * @param key Pointer to the key data. The key size can be 128, 192, or 256 bits.
	 */
	CTwofish(const void *key);

	/**
	 * @brief Encrypts a block of data using the Twofish algorithm.
	 *
	 * @param inData Pointer to the input data (16 bytes).
	 * @param outData Pointer to the output data (16 bytes).
	 */
	void Encrypt(const void *inData, void *outData);

	/**
	 * @brief Encrypts a block of data using the Twofish algorithm in CBC mode.
	 *
	 * @param outData Pointer to the output data (16 bytes).
	 * @param ioPartialOutSize Pointer to the size of the output data. This will be updated with the
	 * actual size of the encrypted data.
	 * @param inData Pointer to the input data (16 bytes).
	 * @param inSize Size of the input data.
	 */
	void EncryptCBC(void *outData, size_t &ioPartialOutSize, const void *inData, size_t inSize);

private:
	uint32_t mSBox[4][256];
	uint32_t mKey[40];

	void EncryptCBCIteration(const void *inData, void *outData);
};
