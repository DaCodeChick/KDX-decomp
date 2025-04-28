#pragma once

#include "typedefs.h"

/**
 * @brief A structure representing a point in 2D space.
 */
struct SPoint
{
	int x; ///< The x-coordinate of the point.
	int y; ///< The y-coordinate of the point.

#ifdef _WIN32
	/**
	 * @brief Converts the SPoint to a POINT structure.
	 * @return A pointer to the POINT structure.
	 */
	operator LPPOINT() const
	{
		return (LPPOINT)this;
	}

	/**
	 * @brief Converts the SPoint to a POINT structure.
	 * @return A POINT structure.
	 */
	operator POINT() const
	{
		return *(LPPOINT)this;
	}

	/**
	 * @brief Converts the SPoint to a POINTL structure.
	 * @return A pointer to the POINTL structure.
	 */
	operator POINTL() const
	{
		return *(POINTL *)this;
	}
#endif // _WIN32
};

/**
 * @brief A structure representing a rectangle in 2D space.
 */
struct SRect
{
	int left;   ///< The left edge of the rectangle.
	int top;    ///< The top edge of the rectangle.
	int right;  ///< The right edge of the rectangle.
	int bottom; ///< The bottom edge of the rectangle.

	/**
	 * @brief Checks if this rectangle intersects with another rectangle.
	 * @param inRect The rectangle to check for intersection with.
	 * @return True if the rectangles intersect, false otherwise.
	 */
	bool Intersects(SRect &inRect) const;

	/**
	 * @brief Get the intersection of two rectangles
	 *
	 * @param inRect
	 * @param outSect
	 * @return true
	 * @return false
	 */
	bool GetIntersection(SRect &inRect, SRect &outSect) const;

	/**
	 * @brief Get the union of two rectangles
	 *
	 * @param inRect
	 * @param outUnion
	 * @return true
	 * @return false
	 */
	bool GetUnion(SRect &inRect, SRect &outUnion) const;

	/**
	 * @brief Constrains the rectangle to fit within the specified maximum rectangle.
	 *
	 * @param inMax The maximum rectangle to constrain to.
	 */
	void Constrain(SRect &inMax);

	/**
	 * @brief Center this rectangle horizontally within the specified base rectangle.
	 *
	 * @param inBase The base rectangle to center within.
	 */
	void CenterHoriz(SRect &inBase);

	/**
	 * @brief This function checks if the rectangle is valid (i.e., if the left edge is less than
	 * the right edge, and the top edge is less than the bottom edge). If the rectangle is invalid,
	 * it corrects the dimensions.
	 */
	void Validate();

#ifdef _WIN32
	/**
	 * @brief Converts the SRect to a RECT structure.
	 * @return A pointer to the RECT structure.
	 */
	operator LPRECT() const
	{
		return (LPRECT)this;
	}

	/**
	 * @brief Converts the SRect to a RECT structure.
	 * @return A RECT structure.
	 */
	operator RECT() const
	{
		return *(LPRECT)this;
	}
#endif // _WIN32
};

constexpr double gm_2Pi = 6.28318530717958647692; ///< Constant representing 2π (2 times pi).
constexpr double gm_Pi = 3.14159265358979323846;  ///< Constant representing π (pi).
