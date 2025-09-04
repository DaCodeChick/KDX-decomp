#pragma once

#include "../common/UCryptTransact.h"

inline void SettingsCrypt(void *ioData, size_t inDataSize)
{
	UCryptTransact::DataCrypt(ioData, inDataSize, 0x35662CB6, 0x41A609FB, 8985);
}
