#pragma once

#include "typedefs.h"

/**
 * @brief A class that implements a list of pointers.
 */
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
	 * @return void*
	 */
	void *PopFront();

private:
	void *mHead, *mTail;
	uint mOffset, mCount;
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
		return (T *)CVoidPtrList::PopFront();
	}
};
