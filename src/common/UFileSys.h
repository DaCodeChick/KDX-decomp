#pragma once

#include "typedefs.h"

/**
 * @brief File system reference structure.
 */
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
	 * @return void*
	 */
	static void *Read(SFileSysRef *inRef, uint inOffset, uint inMaxSize, void *outData,
	                  uint inOptions);

	/**
	 * @brief Write data to the file system reference.
	 *
	 * @param inRef Pointer to the file system reference to which to write data.
	 * @param inData Pointer to the data to be written.
	 * @param inDataSize Size of the data to be written.
	 * @param inOptions Options for writing the data.
	 */
	static void Write(SFileSysRef *inRef, const void *inData, uint inDataSize, uint inOptions);

	/**
	 * @brief Get the size of the file in bytes.
	 *
	 * @param inRef Pointer to the file system reference for which to get the size.
	 * @param inOptions Options for getting the size.
	 * @return ulonglong
	 */
	static ulonglong GetFileSize(SFileSysRef *inRef, uint inOptions);

	/**
	 * @brief Validate the file path.
	 *
	 * @param ioPath Pointer to the file path to be validated.
	 * @param inPathSize Size of the file path.
	 * @return true
	 * @return false
	 */
	static bool ValidateFilePath(char *ioPath, uint inPathSize);
};
