#pragma once

#include "typedefs.h"

/// @brief A class that implements a list of pointers.
class CVoidPtrList
{
public:
	/**
	 * @brief Add an item to the front of the list.
	 *
	 * @param inPtr Pointer to the item to add.
	 */
	void AddFrontItem(void *inPtr);

	/**
	 * @brief Add an item to the back of the list.
	 *
	 * @param inPtr Pointer to the item to add.
	 */
	void AddBackItem(void *inPtr);

	/**
	 * @brief Remove and return the first item in the list.
	 *
	 * @return Pointer to the first item in the list.
	 */
	void *PopFront();

	/**
	 * @brief Remove an item from the list.
	 *
	 * @param inPtr Pointer to the item to remove.
	 * @return true if the item was removed, false otherwise.
	 */
	bool RemoveItem(void *inPtr);

	/**
	 * @brief Check if an item is in the list.
	 *
	 * @param inPtr Pointer to the item to check.
	 * @return true if the item is in the list, false otherwise.
	 */
	bool IsInList(const void *inPtr) const;

	/**
	 * @brief Get the number of items in the list.
	 *
	 * @return The number of items in the list.
	 */
	void *Add(void *inPtr, size_t inSize);

	/**
	 * @brief Remove an item from the list.
	 *
	 * @param inPtr Pointer to the item to remove.
	 * @param inSize Size of the item to remove.
	 * @return Pointer to the removed item.
	 */
	void *Remove(void *inPtr, size_t inSize);

	/**
	 * @brief Insert an item into the list.
	 *
	 * @param inPtr Pointer to the item to insert.
	 * @param inIndex Index at which to insert the item.
	 * @param inSize Size of the item to insert.
	 * @param inFillValue Value to fill the new space with.
	 * @return Pointer to the inserted item.
	 */
	void *Insert(void *inPtr, size_t inIndex, size_t inSize, uint8_t inFillValue);

protected:
	void *mHead, *mTail;
	size_t mOffset, mCount;

	/**
	 * @brief Preallocate memory for the list.
	 *
	 * @param inSize Size of the memory to allocate.
	 * @param inCount Number of items to allocate.
	 */
	void Preallocate(size_t inSize, size_t inCount);

	/**
	 * @brief Allocate a new item in the list.
	 *
	 * @param inSize Size of the item to allocate.
	 */
	void AllocateNewItem(size_t inSize)
	{
		Preallocate(reinterpret_cast<uintptr_t>(mTail) + inSize, 1);
	}
};

/**
 * @brief A class that implements a list of pointers to objects of type T.
 *
 * @tparam T The type of the objects in the list.
 */
template <class T> class CPtrList : public CVoidPtrList
{
public:
	/**
	 * \brief Add an item to the front of the list.
	 * \param inPtr Pointer to the item to add.
	 */
	void AddFrontItem(T *inPtr)
	{
		CVoidPtrList::AddFrontItem(inPtr);
	}

	/**
	 * \brief Add an item to the back of the list.
	 * \param inPtr Pointer to the item to add.
	 */
	void AddBackItem(T *inPtr)
	{
		CVoidPtrList::AddBackItem(inPtr);
	}

	/**
	 * \brief Remove and return the first item in the list.
	 * \return Pointer to the first item in the list.
	 */
	T *PopFront()
	{
		return static_cast<T *>(CVoidPtrList::PopFront());
	}

	/**
	 * \brief Remove an item from the list.
	 * \param inPtr Pointer to the item to remove.
	 * \return true if the item was removed, false otherwise.
	 */
	bool RemoveItem(T *inPtr)
	{
		return CVoidPtrList::RemoveItem(inPtr);
	}

	/**
	 * \brief Check if an item is in the list.
	 * \param inPtr Pointer to the item to check.
	 * \return true if the item is in the list, false otherwise.
	 */
	bool IsInList(const T *inPtr) const
	{
		return CVoidPtrList::IsInList(inPtr);
	}

	/**
	 * \brief Add an item to the list.
	 * \param inPtr Pointer to the item to add.
	 * \param inSize Size of the item to add.
	 * \return Pointer to the added item.
	 */
	T *Add(T *inPtr, size_t inSize)
	{
		return static_cast<T *>(CVoidPtrList::Add(inPtr, inSize));
	}

	/**
	 * \brief Remove an item from the list.
	 * \param inPtr Pointer to the item to remove.
	 * \param inSize Size of the item to remove.
	 * \return Pointer to the removed item.
	 */
	T *Remove(T *inPtr, size_t inSize)
	{
		return static_cast<T *>(CVoidPtrList::Remove(inPtr, inSize));
	}

	/**
	 * \brief Insert an item into the list.
	 * \param inPtr Pointer to the item to insert.
	 * \param inIndex Index at which to insert the item.
	 * \param inSize Size of the item to insert.
	 * \param inFillValue Value to fill the new space with.
	 * \return Pointer to the inserted item.
	 */
	T *Insert(T *inPtr, size_t inIndex, size_t inSize, uint8_t inFillValue)
	{
		return static_cast<T *>(CVoidPtrList::Insert(inPtr, inIndex, inSize, inFillValue));
	}

	/**
	 * \brief Add an item to the list.
	 * \param inItem Item to add.
	 * \return Pointer to the added item.
	 */
	T *AddItem(T inItem)
	{
		auto tail = reinterpret_cast<uintptr_t>(mTail);
		if (tail >= mOffset)
			Preallocate(tail + sizeof(T), 1);

		auto newItem = reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(mHead) + tail * sizeof(T));
		*newItem = inItem;
		mTail = reinterpret_cast<T *>(tail + 1);

		return newItem;
	}

protected:
	void Preallocate(size_t inSize)
	{
		auto size = reinterpret_cast<uintptr_t>(mTail) + inSize;
		if (mOffset < size)
			Preallocate(size, sizeof(T));
	}
};
