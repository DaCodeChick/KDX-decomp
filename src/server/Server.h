#pragma once

#include "../common/CPtrList.h"
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
	SRegularTransport *tpt;
	uint8_t logon[32];
	uint8_t password[32];
	uint32_t key;
	uint8_t state;
	uint16_t drmOffset;
	uint16_t drmSize;
	uint8_t *drm;
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
