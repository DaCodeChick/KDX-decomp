#pragma once

#include "typedefs.h"

struct SRegularTransport;

/**
 * @brief Callback function type for handling incoming connections.
 * @param inListenPort The port on which the connection is being listened to.
 * @param inTpt Pointer to the transport structure associated with the connection.
 * @param inType The type of connection (e.g., TCP, UDP).
 */
typedef void (*TConnectionHandlerProc)(uint16_t inListenPort, SRegularTransport *inTpt, int inType);

/// @brief This structure is used to manage the transport layer of a network connection.
class HXAPI URegularTransport
{
public:
	/// @brief Initializes the transport layer.
	static void Init();

	/**
	 * @brief Creates a new transport layer instance.
	 *
	 * @param inProc Callback function to handle incoming connections.
	 * @param inContext Context pointer to be passed to the callback function.
	 * @param inProtocol The protocol to be used (e.g., TCP, UDP).
	 * @param inMode The mode of operation (e.g., server, client).
	 * @return Pointer to the newly created transport layer instance.
	 */
	[[nodiscard]] static SRegularTransport *New(TConnectionHandlerProc inProc, void *inContext,
	                                            int inProtocol, int inMode);

	/**
	 * @brief Send data through the transport layer.
	 *
	 * @param inTpt Pointer to the transport layer instance.
	 * @param inData Pointer to the data to be sent.
	 * @param inDataSize Size of the data to be sent.
	 */
	static void Send(SRegularTransport *inTpt, const void *inData, size_t inDataSize);

	/**
	 * @brief Receives data from the transport layer.
	 *
	 * @param inTpt Pointer to the transport layer instance.
	 * @param outMaxSize Pointer to store the maximum size of the received data.
	 * @param outHasMoreData Pointer to store whether there is more data to be received.
	 * @return Pointer to the received data.
	 */
	static void *Receive(SRegularTransport *inTpt, size_t *outMaxSize, bool *outHasMoreData);

	/**
	 * @brief Launches a URL in the default web browser.
	 *
	 * @param inText Pointer to the URL string.
	 * @param inTextSize Size of the URL string.
	 */
	static void LaunchURL(const void *inText, size_t inTextSize);
};

enum
{
	transError_Unknown = 0x40064,         ///< Unknown error
	transError_NoData = 0x40067,          ///< No data available
	transError_InvalidData,               ///< Invalid data
	transError_AddressInUse,              ///< Address already in use
	transError_ConnectionReset,           ///< Connection reset
	transError_ConnectionRefused,         ///< Connection refused
	transError_ConnectionTimedOut,        ///< Connection timed out
	transError_HostUnreachable = 0x4006F, ///< Host unreachable
	transError40070,
	transError40074 = 0x40074,
};
