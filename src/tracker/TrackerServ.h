#pragma once

#include "../common/typedefs.h"

class CMyApplication
{
public:
	CMyApplication();
	bool CheckIfBanned(char *inAddr, int inAddrSize);
private:
	uint mSeeds[3];
	uint mPort;
};
