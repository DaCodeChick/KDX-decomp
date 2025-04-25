#pragma once

#include "typedefs.h"

class CVoidPtrList
{
public:
	void AddFrontItem(void *inPtr);
	void AddBackItem(void *inPtr);
	void RemoveItem(void *inPtr);
	void * PopFront();
private:
	void *mHead, *mTail;
	uint mOffset, mCount;
};

template <class T> class CPtrList : public CVoidPtrList
{
public:
	void AddFrontItem(T *inPtr) { CVoidPtrList::AddFrontItem(inPtr); }
	void AddBackItem(T *inPtr) { CVoidPtrList::AddBackItem(inPtr); }
	void RemoveItem(T *inPtr) { CVoidPtrList::RemoveItem(inPtr); }
	T * PopFront() { return (T *)CVoidPtrList::PopFront(); }
};
