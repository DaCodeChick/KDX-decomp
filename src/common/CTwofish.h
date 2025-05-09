#pragma once

#include "typedefs.h"

/// @brief Twofish cipher class
class CTwofish
{
public:
	/**
	 * @brief Constructor
	 * 
	 * @param key Pointer to the key data. The key size can be 128, 192, or 256 bits.
	 */
	CTwofish(const void *key);

	void EncryptFull(const void *inData, void *outData);

	/**
	 * @brief Encrypts a block of data using the Twofish algorithm.
	 * 
	 * @param inData Pointer to the input data (16 bytes).
	 * @param outData Pointer to the output data (16 bytes).
	 */
	void EncryptFast(const void *inData, void *outData);
private:
	uint32_t mSBox[4][256];
	uint32_t mKey[40];
};
