#pragma once

#include "typedefs.h"

/// @brief File system reference structure.
struct SFileSysRef;

/**
 * @brief File system interface class.
 *
 * This class provides an interface for file system operations such as opening files,
 * reading data, writing data, and getting file size. It also includes a method for
 * validating file paths.
 */
class UFileSys
{
public:
	/**
	 * @brief Opens a file system reference.
	 *
	 * This method opens a file system reference for the specified file path.
	 *
	 * @param inRef Pointer to the file system reference to be opened.
	 */
	static void Open(SFileSysRef *inRef);

	/**
	 * @brief Read data from the file system reference.
	 *
	 * @param inRef Pointer to the file system reference from which to read data.
	 * @param inOffset Offset in the file from which to start reading data.
	 * @param inMaxSize Maximum size of data to read.
	 * @param outData Pointer to the buffer where the read data will be stored.
	 * @param inOptions Options for reading the data.
	 * @return Pointer to the buffer containing the read data.
	 */
	static void *Read(SFileSysRef *inRef, size_t inOffset, size_t inMaxSize, void *outData,
	                  unsigned inOptions);

	/**
	 * @brief Write data to the file system reference.
	 *
	 * @param inRef Pointer to the file system reference to which to write data.
	 * @param inData Pointer to the data to be written.
	 * @param inDataSize Size of the data to be written.
	 * @param inOptions Options for writing the data.
	 */
	static void Write(SFileSysRef *inRef, const void *inData, size_t inDataSize,
	                  unsigned inOptions);

	/**
	 * @brief Get the size of the file in bytes.
	 *
	 * @param inRef Pointer to the file system reference for which to get the size.
	 * @param inOptions Options for getting the size.
	 * @return Size of the file in bytes.
	 */
	[[nodiscard]] static size_t GetFileSize(SFileSysRef *inRef, unsigned inOptions);

	/**
	 * @brief Validate the file path.
	 *
	 * @param ioPath Pointer to the file path to be validated.
	 * @param inPathSize Size of the file path.
	 * @return True if the file path is valid, false otherwise.
	 */
	[[nodiscard]] static bool ValidateFilePath(const void *inPath, size_t inPathSize);
};

enum
{
	fsError_NotEnoughSpace = 0x30070,    ///< Not enough space on the device
	fsError_ItemAlreadyExists = 0x30073, ///< File already exists
	fsError_BadData = 0x30074,           ///< Invalid data
	fsError_FileInUse,                   ///< File is in use
	fsError_BadName,                     ///< Invalid file name
};
