#include <gtest/gtest.h>

#include "../src/common/UCryptTransact.h"

TEST(Crypto, Generic)
{
	char testData[] = "Test data for encryption and decryption.";
	const size_t dataSize = std::strlen(testData) + 1;

	UCryptTransact::UDPPacketCrypt(testData, dataSize);
	UCryptTransact::UDPPacketCrypt(testData, dataSize);
	EXPECT_EQ(true,
	          UMemory::Compare(testData, "Test data for encryption and decryption.", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, BlockCrypt1B20E200)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);

	UCryptTransact::BlockCrypt1B20E200(testData, false);
	UCryptTransact::BlockCrypt1B20E200(testData, true);
	EXPECT_EQ(true, UMemory::Compare(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, BlockCrypt6E7DFD34)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);

	UCryptTransact::BlockCrypt6E7DFD34(testData, false);
	UCryptTransact::BlockCrypt6E7DFD34(testData, true);
	EXPECT_EQ(true, UMemory::Compare(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, TCPPacketCrypt)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);
	const uint32_t initValue = 0xDEADBEEF;

	UCryptTransact::TCPPacketCrypt(initValue, testData, dataSize);
	UCryptTransact::TCPPacketCrypt(initValue, testData, dataSize);
	EXPECT_EQ(true, UMemory::Compare(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, KeyGeneration)
{
	const char testData[] = "Hello, World!";
	const size_t testDataSize = strlen(testData);
	uint8_t key[32] = {0};
	UCryptTransact::GenerateKey(testData, testDataSize, key);
	EXPECT_EQ(true, UMemory::Compare(
	                    key,
	                    "\x24\x80\xFC\x9F\x93\xC5\xA3\x83\xBE\x4A\xCD\x20\x77\xA2\x0D\x2A\x00"
	                    "\x00\x00\x00\x24\x80\xFC\x9F\x93\xC5\xA3\x83\xE0\x7F\x2E\x50",
	                    32));
}
