#pragma once

#include "typedefs.h"

/// @brief A structure representing a point in 2D space.
struct SPoint
{
	int x; ///< The x-coordinate of the point.
	int y; ///< The y-coordinate of the point.

#ifdef _WIN32
	/**
	 * @brief Converts the SPoint to a POINT structure.
	 * @return A pointer to the POINT structure.
	 */
	constexpr operator LPPOINT() const
	{
		return (LPPOINT)this;
	}

	/**
	 * @brief Converts the SPoint to a POINT structure.
	 * @return A POINT structure.
	 */
	constexpr operator POINT() const
	{
		return *(LPPOINT)this;
	}

	/**
	 * @brief Converts the SPoint to a POINTL structure.
	 * @return A pointer to the POINTL structure.
	 */
	constexpr operator POINTL() const
	{
		return *(POINTL *)this;
	}
#endif // _WIN32
};

enum
{
	alignOption_Left = 0x0001,        ///< Align to the left edge.
	alignOption_Top = 0x0002,         ///< Align to the top edge.
	alignOption_Right = 0x0004,       ///< Align to the right edge.
	alignOption_Bottom = 0x0008,      ///< Align to the bottom edge.
	alignOption_CenterHoriz = 0x0010, ///< Align to the center horizontally.
	alignOption_CenterVert = 0x0020,  ///< Align to the center vertically.
	alignOption_ClipHoriz = 0x0040,   ///< Align to the left edge and clip horizontally.
	alignOption_ClipVert = 0x0080,    ///< Align to the top edge and clip vertically.
};

/// @brief A structure representing a rectangle in 2D space.
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
	[[nodiscard]] constexpr bool Intersects(const SRect &inRect) const
	{
		return !(inRect.left >= right || inRect.right <= left || inRect.top >= bottom ||
		         inRect.bottom <= top);
	}

	/**
	 * @brief Get the intersection of two rectangles
	 *
	 * @param inRect
	 * @param outSect
	 */
	bool GetIntersection(const SRect &inRect, SRect &outSect) const;

	/**
	 * @brief Get the union of two rectangles
	 *
	 * @param inRect
	 * @param outUnion
	 */
	bool GetUnion(const SRect &inRect, SRect &outUnion) const;

	/**
	 * @brief Constrains the rectangle to fit within the specified maximum rectangle.
	 *
	 * @param inMax The maximum rectangle to constrain to.
	 */
	void Constrain(const SRect &inMax);

	void Center(const SRect &inBase, const SRect &inContainer);

	/**
	 * @brief Center this rectangle horizontally within the specified base rectangle.
	 *
	 * @param inBase The base rectangle to center within.
	 */
	void CenterHoriz(const SRect &inBase);

	void MoveTo(const SRect &inRect, int inLeft, int inTop);

	/**
	 * @brief This function checks if the rectangle is valid (i.e., if the left edge is less than
	 * the right edge, and the top edge is less than the bottom edge). If the rectangle is invalid,
	 * it corrects the dimensions.
	 */
	void Validate();

	void Align(const SRect &inSourceRect, unsigned inOptions, const SRect &inRefRect);

#ifdef _WIN32
	/**
	 * @brief Converts the SRect to a RECT structure.
	 * @return A pointer to the RECT structure.
	 */
	constexpr operator LPRECT() const
	{
		return (LPRECT)this;
	}

	/**
	 * @brief Converts the SRect to a RECT structure.
	 * @return A RECT structure.
	 */
	constexpr operator RECT() const
	{
		return *(LPRECT)this;
	}
#endif // _WIN32
};

/**
 * @brief Constant representing 2π (2 times pi).
 * @details This constant is used in various mathematical calculations, particularly in
 * trigonometry.
 */
constexpr double gm_2Pi = 6.28318530717958647692;

/**
 * @brief Constant representing π (pi).
 * @details This constant is used in various mathematical calculations, particularly in
 * trigonometry.
 */
constexpr double gm_Pi = 3.14159265358979323846;
