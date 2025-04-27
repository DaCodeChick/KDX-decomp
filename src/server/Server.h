#pragma once

#include "../common/CPtrList.h"
#include "../common/UFileSys.h"
#include "../common/URegularTransport.h"

struct BanRecord
{
	longlong expires;
	byte *addr;
	byte *info;
};

struct SMyClient
{
	uint tag;
	uint magic;
	SRegularTransport *tpt;
	byte logon[32];
	byte password[32];
	uint key;
	byte state;
	ushort drmOffset;
	ushort drmSize;
	byte *drm;
};

struct SMyChat
{
	SMyChat *next;
	uint id;
	longlong created;
	byte name[64];
	byte subject[128];
	byte drmMsg[128];
	byte drmUser[64];
};

class CMyApplication
{
public:
	CMyApplication();
	void StartServer();
	bool CheckIfBanned(char *inAddr, int inAddrSize) const;

private:
	SRegularTransport *mMainTpt, *mAltTpt, *mAdminTpt;
	CPtrList<SMyChat> mChats;
	SFileSysRef *mDefaultDir, *mBaseDir, *mAccountsDB, *mNewsDB;
	uint mBanCount;
	BanRecord *mBans;
	byte mName[32];
	uint mClientPort, mAltPort, mAdminPort;
	uint mSeeds[3];
};
