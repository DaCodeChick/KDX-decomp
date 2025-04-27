#include "CPtrList.h"

void CVoidPtrList::AddFrontItem(void *inPtr)
{
	if (!inPtr)
		return;

	void *prevHead = mHead;
	*(void **)((uint)inPtr + mOffset) = prevHead;
	mHead = inPtr;

	if (!prevHead)
		mTail = inPtr;

	mCount++;
}

void CVoidPtrList::AddBackItem(void *inPtr)
{
	if (!inPtr)
		return;

	*(void **)((uint)inPtr + mOffset) = NULL;

	if (!mTail)
		mHead = inPtr;
	else
		*(void **)((uint)mTail + mOffset) = inPtr;

	mTail = inPtr;
	mCount++;
}
