#include <cstring>
#include <gtest/gtest.h>

#include "../src/common/UCryptTransact.h"

TEST(Crypto, Generic)
{
	char testData[] = "Test data for encryption and decryption.";
	const size_t dataSize = std::strlen(testData) + 1;

	UCryptTransact::UDPPacketCrypt(testData, dataSize);
	UCryptTransact::UDPPacketCrypt(testData, dataSize);
	EXPECT_EQ(0, std::memcmp(testData, "Test data for encryption and decryption.", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, BlockCrypt1B20E200)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);

	UCryptTransact::BlockCrypt1B20E200(testData, false);
	UCryptTransact::BlockCrypt1B20E200(testData, true);
	EXPECT_EQ(0, std::memcmp(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, BlockCrypt6E7DFD34)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);

	UCryptTransact::BlockCrypt6E7DFD34(testData, false);
	UCryptTransact::BlockCrypt6E7DFD34(testData, true);
	EXPECT_EQ(0, std::memcmp(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}

TEST(Crypto, TCPPacketCrypt)
{
	char testData[] = "01234567890ABCDEF";
	const size_t dataSize = std::strlen(testData);
	const uint32_t initValue = 0xDEADBEEF;

	UCryptTransact::TCPPacketCrypt(initValue, testData, dataSize);
	UCryptTransact::TCPPacketCrypt(initValue, testData, dataSize);
	EXPECT_EQ(0, std::memcmp(testData, "01234567890ABCDEF", dataSize))
	    << "Data should be unchanged after double encryption/decryption.";
}
