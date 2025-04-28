#pragma once

#include "typedefs.h"

/// @brief Twofish encryption context structure.
struct STwofish;

class UCryptTransact
{
public:
	/**
	 * @brief Encrypts the given data using the Twofish algorithm.
	 * @param ioCtx The Twofish context to use for encryption.
	 * @param inData The input data to encrypt.
	 * @param outData The output buffer for the encrypted data.
	 */
	static void TwofishEncrypt(STwofish &ioCtx, const void *inData, void *outData);

	/**
	 * @brief Encrypts the given data using the Twofish algorithm.
	 * @param ioCtx The Twofish context to use for encryption.
	 * @param inData The input data to encrypt.
	 * @param outData The output buffer for the encrypted data.
	 */
	static void TwofishEncryptSimple(STwofish &ioCtx, const void *inData, void *outData);
};
