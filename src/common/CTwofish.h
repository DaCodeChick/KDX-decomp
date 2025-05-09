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

	void Encrypt(const void *inData, void *outData);

	/**
	 * @brief Simple encryption function
	 * 
	 * @param inData Pointer to the input data. The size should be 16 bytes (128 bits).
	 * @param outData Pointer to the output data. The size should be 16 bytes (128 bits).
	 */
	void EncryptSimple(const void *inData, void *outData);
private:
	uint32_t mSBox[4][256];
	uint32_t mKey[40];
};
