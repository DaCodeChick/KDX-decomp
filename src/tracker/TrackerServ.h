#pragma once

#include "../common/typedefs.h"

class CMyApplication
{
public:
	CMyApplication();
	bool CheckIfBanned(const char *inAddr, size_t inAddrSize);

private:
	uint32_t mSeeds[3];
	uint16_t mPort;
};
