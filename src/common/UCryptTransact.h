#pragma once

#include "UMemory.h"

/**
 * @brief Typedef for a function pointer that represents a cryptographic procedure.
 * @param ioData Pointer to the data to be processed.
 * @param isDecrypt Flag indicating whether to decrypt (true) or encrypt (false).
 */
typedef void (*TCryptProc)(void *ioData, bool isDecrypt);

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
	static void DataCrypt(void *ioData, size_t inDataSize, unsigned inInit, unsigned inMultiplier,
	                      unsigned inAddend);

	/**
	 * @brief Encrypts or decrypts the given data using a specific algorithm.
	 *
	 * @param inInit Initial value for the encryption/decryption process.
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param inDataSize Size of the data to be processed.
	 */
	static void TCPPacketCrypt(unsigned inInit, void *ioData, size_t inDataSize);

	/**
	 * @brief Generates a key based on the given data.
	 *
	 * @param inData Pointer to the data used to generate the key.
	 * @param inDataSize Size of the data.
	 * @param outKey Pointer to the generated key.
	 */
	static void GenerateKey(const void *inData, size_t inDataSize, void *outKey);

	/**
	 * @brief Checks if the given key is a default key.
	 *
	 * @param inKey Pointer to the key to be checked.
	 * @return True if the key is a default key, false otherwise.
	 */
	static bool IsDefaultKey(const void *inKey)
	{
		return UMemory::Compare(inKey, sDefaultKey, 32);
	}

	/**
	 * @brief Encrypts or decrypts the given data using a specific algorithm.
	 *
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param inDataSize Size of the data to be processed.
	 */
	static void UDPPacketCrypt(void *ioData, size_t inDataSize)
	{
		DataCrypt(ioData, inDataSize, 0xA5A16C4A, 0x41D28485, 12843);
	}

private:
	static constexpr uint32_t sDefaultKey[8] = {0xeea339da, 0x6ebeaeca, 0xd4b6b5e,  0xba298eba,
	                                            0xefbf5532, 0xc4b5a218, 0x90186095, 0x907d8af};
};
