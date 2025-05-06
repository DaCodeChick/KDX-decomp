#include "CPtrList.h"

void CVoidPtrList::AddFrontItem(void *inPtr)
{
	if (!inPtr)
		return;

	auto prevHead = mHead;
	*(void **)((size_t)inPtr + mOffset) = prevHead;
	mHead = inPtr;

	if (!prevHead)
		mTail = inPtr;

	mCount++;
}

void CVoidPtrList::AddBackItem(void *inPtr)
{
	if (!inPtr)
		return;

	*(void **)((size_t)inPtr + mOffset) = NULL;

	if (!mTail)
		mHead = inPtr;
	else
		*(void **)((size_t)mTail + mOffset) = inPtr;

	mTail = inPtr;
	mCount++;
}
