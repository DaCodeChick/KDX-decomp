#pragma once

#include "typedefs.h"

/**
 * @brief Structure to hold mouse message data.
 */
struct SMouseMsgData
{
	longlong time; ///< Timestamp of the mouse event.
	uint flags;    ///< Flags indicating the type of mouse event.
	uint mods;     ///< Modifier keys state (e.g., Shift, Ctrl).
	int x;         ///< X-coordinate of the mouse position.
	int y;         ///< Y-coordinate of the mouse position.
	byte button;   ///< Button that was pressed or released.
	short misc;    ///< Miscellaneous information about the event.
};

/**
 * @brief Structure to hold keyboard message data.
 */
struct SKeyMsgData
{
	longlong timestamp; ///< Timestamp of the keyboard event.
	uint type;          ///< Type of keyboard event (e.g., key press, key release).
	uint modifierState; ///< Modifier keys state (e.g., Shift, Ctrl).
	uint unicodeChar;   ///< Unicode character code of the key pressed.
	ushort asciiChar;   ///< ASCII character code of the key pressed.
	ushort reserved;    ///< Reserved for future use.
};

/**
 * @brief This function is called when a message is received, and it can be used to handle the
 * message accordingly.
 * @param inContext Pointer to the context in which the message is processed.
 */
typedef void (*TMessageProc)(void *inContext);
