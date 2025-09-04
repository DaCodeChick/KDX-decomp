#pragma once

#include "../common/CPtrList.h"
#include "../common/CTwofish.h"
#include "../common/UCryptTransact.h"
#include "../common/UFileSys.h"
#include "../common/URegularTransport.h"

struct SMyAccount
{
};

struct BanRecord
{
	int64_t expires;
	uint8_t *addr;
	uint8_t *info;
};

struct SMyClient
{
	unsigned tag;
	uint32_t magic;
	TCryptProc cryptProc;
	SRegularTransport *tpt;
	uint32_t offs1C; // random seed?
	uint8_t logon[32];
	uint8_t password[32];
	uint32_t userID;
	uint64_t offs74; // login timestamp? used for XORing
	uint32_t offs7C; // random seed?
	uint8_t state;
	uint16_t drmOffset;
	uint16_t drmSize;
	const char *drm;
	uint32_t offsA8; // buffer count?
	void *offsAC;    // buffer end?
	uint32_t offsB0; // total buffer size?
	void *offsB4;    // buffer array?
	void *offsB8;    // buffer array end?
	uint8_t iv[32];  // input vector for Twofish
	CTwofish twofishContext;
};

struct SMyChat
{
	SMyChat *next;
	uint32_t id;
	int64_t created;
	uint8_t name[64];
	uint8_t subject[128];
	uint8_t drmMsg[128];
	uint8_t drmUser[64];
};

class CMyApplication
{
public:
	CMyApplication();
	void StartServer();
	bool CheckIfBanned(const void *inAddr, size_t inAddrSize) const;
	SRegularTransport *FindTransportByID(uint32_t inID) const;
private:
	SRegularTransport *mMainTpt, *mAltTpt, *mAdminTpt;
	CPtrList<SMyChat> mChats;
	SFileSysRef *mDefaultDir, *mBaseDir, *mAccountsDB, *mNewsDB;
	size_t mBanCount;
	BanRecord *mBans;
	uint8_t mName[32];
	uint16_t mClientPort, mAltPort, mAdminPort;
	uint32_t mSeeds[3];
};

inline void AccountsDBCrypt(void *ioData, size_t inDataSize)
{
	UCryptTransact::DataCrypt(ioData, inDataSize, 0x9AD22861, 0x41C64E6D, 12345);
}
