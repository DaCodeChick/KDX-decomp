#pragma once

#include "typedefs.h"

/// @brief Structure to hold mouse message data.
struct SMouseMsgData
{
	int64_t time; ///< Timestamp of the mouse event.
	uint32_t flags;    ///< Flags indicating the type of mouse event.
	uint32_t mods;     ///< Modifier keys state (e.g., Shift, Ctrl).
	int x;         ///< X-coordinate of the mouse position.
	int y;         ///< Y-coordinate of the mouse position.
	uint8_t button;   ///< Button that was pressed or released.
	short misc;    ///< Miscellaneous information about the event.
};

/// @brief Structure to hold keyboard message data.
struct SKeyMsgData
{
	int64_t timestamp; ///< Timestamp of the keyboard event.
	uint32_t type;          ///< Type of keyboard event (e.g., key press, key release).
	uint32_t modifierState; ///< Modifier keys state (e.g., Shift, Ctrl).
	uint32_t unicodeChar;   ///< Unicode character code of the key pressed.
	uint16_t asciiChar;   ///< ASCII character code of the key pressed.
	short reserved;    ///< Reserved for future use.
};

/**
 * @brief This function is called when a message is received, and it can be used to handle the
 * message accordingly.
 * @param inContext Pointer to the context in which the message is processed.
 */
typedef void (*TMessageProc)(void *inContext);
