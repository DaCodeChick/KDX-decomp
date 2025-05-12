#include "CPtrList.h"

#include "UMemory.h"

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

bool CVoidPtrList::RemoveItem(void *inPtr)
{
	if (!inPtr)
		return false;

	auto current = mHead;
	void *previous = NULL;

	while (current)
	{
		if (current == inPtr)
		{
			auto next = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(current) + mOffset);
			if (!previous)
				mHead = next;
			else
				*(void **)((size_t)previous + mOffset) = next;

			if (!next)
				mTail = previous;

			mCount--;
			return true;
		}

		previous = current;
		current = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(current) + mOffset);
	}

	return false;
}

void *CVoidPtrList::PopFront()
{
	if (!mHead)
		return NULL;

	auto front = mHead;
	mHead = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(mHead) + mOffset);

	if (!mHead)
		mTail = NULL;

	mCount--;
	return front;
}

bool CVoidPtrList::IsInList(const void *inPtr) const
{
	if (!inPtr)
		return false;

	auto current = mHead;
	while (current)
	{
		if (current == inPtr)
			return true;

		current = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(current) + mOffset);
	}

	return false;
}

void CVoidPtrList::Preallocate(size_t inSize, size_t inCount)
{
	auto requiredSize = inCount * inSize;
	UMemory::Align(requiredSize);

	if (requiredSize / inSize != mOffset)
	{
		void *newMemory = UMemory::Reallocate(mHead, requiredSize);
		if (newMemory)
		{
			mHead = newMemory;
			mOffset = requiredSize / inSize;
		}
	}
}

void *CVoidPtrList::Add(void *inPtr, size_t inSize)
{
	auto head = reinterpret_cast<uintptr_t>(mHead);
	auto tail = reinterpret_cast<uintptr_t>(mTail);
	auto newTail = reinterpret_cast<void *>(tail + inSize);

	if (reinterpret_cast<uintptr_t>(newTail) > (head + mOffset))
		Preallocate(inSize, mCount + 1);

	if (inPtr)
		UMemory::Move(reinterpret_cast<void *>(head + tail), inPtr, inSize);

	auto oldTail = mTail;
	mTail = newTail;
	mCount++;

	return oldTail;
}

void *CVoidPtrList::Remove(void *inPtr, size_t inSize)
{
	auto tail = reinterpret_cast<uintptr_t>(mTail);
	auto head = reinterpret_cast<uintptr_t>(mHead);
	auto target = reinterpret_cast<uintptr_t>(inPtr);

	if (target >= tail)
		return mTail;

	auto remainingSize = tail - target;
	if (remainingSize < inSize)
		inSize = remainingSize;

	if (inSize)
	{
		auto dest = reinterpret_cast<void *>(head + (target - head));
		UMemory::Move(dest, reinterpret_cast<void *>(target + inSize), remainingSize - inSize);
		mTail = reinterpret_cast<void *>(tail - inSize);
		Preallocate(tail - head - inSize, 1);
	}

	return inPtr;
}

void *CVoidPtrList::Insert(void *inPtr, size_t inIndex, size_t inSize, uint8_t inFillValue)
{
	auto tail = reinterpret_cast<uintptr_t>(mTail);
	auto head = reinterpret_cast<uintptr_t>(mHead);
	auto insertPos = head + (inIndex * inSize);

	auto newTail = reinterpret_cast<void *>(tail + inSize);
	if (newTail > reinterpret_cast<void *>(head + mOffset))
	{
		Preallocate(inSize, mCount + 1);
		head = reinterpret_cast<uintptr_t>(mHead);
		insertPos = head + (inIndex * inSize);
	}

	UMemory::Move(reinterpret_cast<void *>(insertPos + inSize), reinterpret_cast<void *>(insertPos),
	              tail - insertPos);
	UMemory::Fill(reinterpret_cast<void *>(insertPos), inSize, inFillValue);

	mTail = newTail;
	mCount++;

	return reinterpret_cast<void *>(insertPos);
}

void *CVoidPtrList::Insert(void *inOffset, void *inData, size_t inDataSize)
{
	auto oldTail = mTail;
	auto insertPos = reinterpret_cast<uintptr_t>(inOffset);
	auto head = reinterpret_cast<uintptr_t>(mHead);
	auto tail = reinterpret_cast<uintptr_t>(mTail);

	if (insertPos > tail)
		insertPos = tail;

	if (inDataSize)
	{
		auto newTail = reinterpret_cast<void *>(tail + inDataSize);

		if (reinterpret_cast<uintptr_t>(newTail) > head + mOffset)
		{
			Preallocate(inDataSize, mCount + 1);
			oldTail = mTail;
			insertPos = head + (insertPos - head);
		}

		UMemory::Move(reinterpret_cast<void *>(insertPos + inDataSize), inOffset, tail - insertPos);

		if (inData)
			UMemory::Move(inOffset, inData, inDataSize);

		mTail = newTail;
		mCount++;
	}

	return inOffset;
}
