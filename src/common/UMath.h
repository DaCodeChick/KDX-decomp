#pragma once

#include "typedefs.h"

/**
 * @brief A collection of math functions.
 */
class UMath
{
public:
	/**
	 * @brief Returns a random seed based on the current time.
	 *
	 * @return uint
	 */
	static uint CalcRandomSeed();

	/**
	 * @brief Generates a random number between 0 and 0xFFFFFFFF.
	 *
	 * @return uint
	 */
	static uint GetRandom();

	/**
	 * @brief Generates a random number between inMin and inMax.
	 *
	 * @param inInit The initial seed value.
	 * @param inMin The minimum value.
	 * @param inMax The maximum value.
	 * @return uint
	 */
	static constexpr uint GetRandom(uint &inInit, uint inMin, uint inMax);

	/**
	 * @brief Generates random data of size inDataSize into ioData.
	 *
	 * @param ioData A pointer to the data buffer to fill with random data.
	 * @param inDataSize The size of the data buffer in bytes.
	 */
	static void GetRandom(void *ioData, uint inDataSize);

	/**
	 * @brief Normalizes an angle to the range [0, 2π).
	 *
	 * @param x The angle in radians.
	 * @return constexpr double
	 */
	static constexpr double NormalizeAngle(double x);

	static constexpr double Sine(double x);
	static constexpr double Cosine(double x);
	static constexpr double ArcTangent(double x);
	static constexpr double SquareRoot(double x);
};
