#pragma once

#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#undef min
#undef max
#endif // _WIN32

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define IS_LITTLE_ENDIAN
#endif
#elif defined(_WIN32) || defined(__i386__) || defined(__x86_64__)
#define IS_LITTLE_ENDIAN
#endif

/**
 * @brief swap bytes in 16-bit value
 *
 * @param x 16-bit value to swap
 * @return swapped 16-bit value
 */
constexpr uint16_t bswap16(uint16_t x) noexcept
{
	return ((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8);
}

/**
 * @brief swap bytes in 32-bit value
 *
 * @param x 32-bit value to swap
 * @return swapped 32-bit value
 */
constexpr uint32_t bswap32(uint32_t x) noexcept
{
	return ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) |
	       ((x & 0x000000FF) << 24);
}

/**
 * @brief swap bytes in 64-bit value
 *
 * @param x 64-bit value to swap
 * @return swapped 64-bit value
 */
constexpr uint64_t bswap64(uint64_t x) noexcept
{
	return ((x & 0xFF00000000000000ULL) >> 56) | ((x & 0x00FF000000000000ULL) >> 40) |
	       ((x & 0x0000FF0000000000ULL) >> 24) | ((x & 0x000000FF00000000ULL) >> 8) |
	       ((x & 0x00000000FF000000ULL) << 8) | ((x & 0x0000000000FF0000ULL) << 24) |
	       ((x & 0x000000000000FF00ULL) << 40) | ((x & 0x00000000000000FFULL) << 56);
}

#ifndef _WIN32
/**
 * @brief Host to Network Short
 *
 * @param x 16-bit value to convert
 * @return converted 16-bit value
 */
constexpr uint16_t htons(uint16_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap16(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Host to Network Long
 *
 * @param x 32-bit value to convert
 * @return converted 32-bit value
 */
constexpr uint32_t htonl(uint32_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap32(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}
#endif // _WIN32

/**
 * @brief Host to Network Long Long
 *
 * @param x 64-bit value to convert
 * @return converted 64-bit value
 */
constexpr uint64_t htonll(uint64_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap64(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}


#ifndef _WIN32
/**
 * @brief Network to Host Short
 *
 * @param x 16-bit value to convert
 * @return converted 16-bit value
 */
constexpr uint16_t ntohs(uint16_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap16(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Network to Host Long
 *
 * @param x 32-bit value to convert
 * @return converted 32-bit value
 */
constexpr uint32_t ntohl(uint32_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap32(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}
#endif // _WIN32

/**
 * @brief Network to Host Long Long
 *
 * @param x 64-bit value to convert
 * @return converted 64-bit value
 */
constexpr uint64_t ntohll(uint64_t x) noexcept
{
#ifdef IS_LITTLE_ENDIAN
	return bswap64(x);
#else
	return x;
#endif // IS_LITTLE_ENDIAN
}

/**
 * @brief Get the minimum of two values
 *
 * @param a first value
 * @param b second value
 * @return minimum value
 */
template <class T> constexpr T min(T a, T b) noexcept
{
	return (a < b) ? a : b;
}

/**
 * @brief Get the maximum of two values
 *
 * @param a first value
 * @param b second value
 * @return maximum value
 */
template <class T> constexpr T max(T a, T b) noexcept
{
	return (a > b) ? a : b;
}

/**
 * @brief Rotate left
 *
 * @param x value to rotate
 * @param n number of bits to rotate
 * @return rotated value
 */
template <class T> constexpr T rotl(T x, unsigned n)
{
	return (x << n) | (x >> ((sizeof(T) << 3) - n));
}

/**
 * @brief Rotate right
 *
 * @param x value to rotate
 * @param n number of bits to rotate
 * @return rotated value
 */
template <class T> constexpr T rotr(T x, unsigned n)
{
	return (x >> n) | (x << ((sizeof(T) << 3) - n));
}

/**
 * @brief Swap two values
 *
 * @param a first value
 * @param b second value
 */
template <class T> void swap(T &a, T &b) noexcept
{
	T temp = a;
	a = b;
	b = temp;
}
