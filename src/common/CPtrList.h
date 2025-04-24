#pragma once

#include "typedefs.h"

class CVoidPtrList
{
private:
	void *mHead, *mTail;
	uint mOffset, mCount;
};

template <class T> class CPtrList : public CVoidPtrList
{
public:
};
