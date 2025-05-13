#pragma once

#include <cmath>

#include "GrafTypes.h"

/// @brief A collection of math functions.
class UMath
{
public:
	/**
	 * @brief Returns a random seed based on the current time.
	 *
	 * @return A random seed value.
	 */
	[[nodiscard]] static unsigned CalcRandomSeed();

	/**
	 * @brief Generates a random number between 0 and 0xFFFFFFFF.
	 *
	 * @return A random number between 0 and 0xFFFFFFFF.
	 */
	[[nodiscard]] static unsigned GetRandom();

	/**
	 * @brief Generates a random number between inMin and inMax.
	 *
	 * @param inInit The initial seed value.
	 * @param inMin The minimum value.
	 * @param inMax The maximum value.
	 * @return A random number between inMin and inMax.
	 */
	[[nodiscard]] static unsigned GetRandom(unsigned &inInit, unsigned inMin, unsigned inMax);

	/**
	 * @brief Generates random data of size inDataSize into ioData.
	 *
	 * @param ioData A pointer to the data buffer to fill with random data.
	 * @param inDataSize The size of the data buffer in bytes.
	 */
	static void GetRandom(void *ioData, size_t inDataSize);

	/**
	 * @brief Normalizes an angle to the range [0, 2π).
	 *
	 * @param x The angle in radians.
	 * @return The normalized angle in radians.
	 */
	[[nodiscard]] static constexpr double NormalizeAngle(double x)
	{
		x = std::fmod(x, gm_2Pi);
		if (x < 0)
			x += gm_2Pi;

		return x;
	}

	/**
	 * @brief Computes the sine of an angle in radians.
	 *
	 * @param x The angle in radians.
	 * @return The sine of the angle.
	 */
	[[nodiscard]] static constexpr double Sine(double x)
	{
		x = NormalizeAngle(x);
		return std::sin(x);
	}

	/**
	 * @brief Computes the cosine of an angle in radians.
	 *
	 * @param x The angle in radians.
	 * @return The cosine of the angle.
	 */
	[[nodiscard]] static constexpr double Cosine(double x)
	{
		x = NormalizeAngle(x);
		return std::cos(x);
	}

	/**
	 * @brief Computes the arc tangent of y/x in radians.
	 *
	 * @param x The x-coordinate.
	 * @return The arc tangent of y/x in radians.
	 */
	[[nodiscard]] static constexpr double ArcTangent(double x)
	{
		return std::atan(x);
	}

	[[nodiscard]] static constexpr double SquareRoot(double x)
	{
		return std::sqrt(x);
	}

	/**
	 * @brief Computes the tangent of an angle in radians.
	 *
	 * @param x The angle in radians.
	 * @return The tangent of the angle.
	 */
	[[nodiscard]] static constexpr double Tangent(double x)
	{
		return std::tan(x);
	}
};
