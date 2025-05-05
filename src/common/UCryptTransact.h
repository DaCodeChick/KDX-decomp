#pragma once

#include "typedefs.h"

/// @brief Twofish encryption context structure.
struct STwofish;

class UCryptTransact
{
public:
	/**
	 * @brief Encrypts or decrypts the given data using a specific algorithm.
	 * 
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param isDecrypt Flag indicating whether to decrypt (true) or encrypt (false).
	 */
	static void BlockCrypt1B20E200(void *ioData, bool isDecrypt);

	/**
	 * @brief Encrypts or decrypts the given data using a specific algorithm.
	 * 
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param isDecrypt Flag indicating whether to decrypt (true) or encrypt (false).
	 */
	static void BlockCrypt6E7DFD34(void *ioData, bool isDecrypt);

	/**
	 * @brief Encrypts or decrypts the given data using a simple algorithm.
	 * 
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param inDataSize Size of the data to be processed.
	 * @param inInit Initial value for the encryption/decryption process.
	 * @param inMultiplier Multiplier value for the encryption/decryption process.
	 * @param inAddend Addend value for the encryption/decryption process.
	 */
	static void DataCrypt(void *ioData, size_t inDataSize, unsigned inInit, unsigned inMultiplier, unsigned inAddend);
	
	/**
	 * @brief Encrypts or decrypts the given data using a specific algorithm.
	 * 
	 * @param inInit Initial value for the encryption/decryption process.
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param inDataSize Size of the data to be processed.
	 */
	static void TCPPacketCrypt(unsigned inInit, void *ioData, size_t inDataSize);
	
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

	static void UDPPacketCrypt(void *ioData, size_t inDataSize)
	{
		DataCrypt(ioData, inDataSize, 0xA5A16C4A, 0x41D28485, 12843);
	}
};
