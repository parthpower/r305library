/**
 * \file
 * \brief Implementation of r305Parser functions
 *
 */
#include "r305Parser.h"
#include <inttypes.h>

/**
 * @brief Get default package structure filled with given parameters.
 * @param pid data_package::pid byte to define type of package of the package from \link PID \endlink definitions.
 * @param length data_package::length Parameter of package, use \link Length \endlink definitions.
 * @param data data_package::data Array of bytes to set as data of the package.
 * @return data_package structure with defaults settings and specified configurations.
 */
data_package getBasePackage(uint8_t pid, uint16_t length, uint8_t* data) {
	uint16_t i = 0;

	data_package package = getDefaultPackage(pid);
	package.length = length;
	package.data_size = package.length - sizeof(package.checksum);
	for (i = 0; i < package.data_size; i++) {
		package.data[package.data_size - i - 1] = data[i];
	}
	autoSetChecksum(&package);
	autoSetPackageSize(&package);
	stringyfyPackage(&package);
	package.ack_command_code = package.data[package.data_size];

	return package;
}

/**
 * @brief Get empty package with default settings
 * @param pid data_package::pid byte to define type of package of the package from \link PID \endlink definitions.
 * @return data_package structure with defaults settings
 */
data_package getDefaultPackage(uint8_t pid) {
	data_package package;
	package.header = DEFAULT_HEADER;
	package.address = DEFAULT_ADDRESS;
	package.pid = pid;
	return package;
}

/**
 * @brief Same as \link getDefaultPackage\endlink(ACK_PACKAGE)
 * @return package with default settings and empty data.
 */
data_package getAckPackage() {
	return getDefaultPackage(ACK_PACKAGE);
}

/**
 * @brief Get command package.
 * @param length data_package::length Parameter of package, use \link Length \endlink definitions.
 * @param data data_package::data Array of bytes to set as data of the package.
 * @return command package with default settings and specified configurations.
 */
data_package getCommandPackage(uint16_t length, uint8_t* data) {
	return getBasePackage(COMMAND_PACKAGE, length, data);

}

/**
 * @brief Calculates and sets the data_package::checksum bytes in package.
 * @param package pointer to a data_package.
 * @return Calculated checksum bytes.
 */
uint16_t autoSetChecksum(data_package *package) {
	uint16_t i = 0;
	package->checksum = (uint16_t) package->pid + (uint16_t) package->length;
	for (i = 0; i < package->length - sizeof(package->checksum); i++) {
		package->checksum += (uint16_t) package->data[i];
	}
	return package->checksum;
}

/**
 * @brief Calculate and set data_package::package_size parameter.
 * @param package pointer to a data_package.
 * @return Calculated size of package.
 */
uint32_t autoSetPackageSize(data_package *package) {
	package->package_size = sizeof(package->header) + sizeof(package->address)
			+ sizeof(package->pid) + sizeof(package->length) + package->length;
	return package->package_size;
}

/**
 * @brief Convert data_package structure to byte string and set data_package::package_string parameter.
 * @param package pointer to a data_package.
 * @return byte string of input data_package.
 */
uint8_t* stringyfyPackage(data_package *package) {
	uint16_t i = 0;
	package->package_string[0] = package->header >> 8;
	package->package_string[1] = package->header;

	package->package_string[2] = package->address >> 8 * 3;
	package->package_string[3] = package->address >> 8 * 2;
	package->package_string[4] = package->address >> 8 * 1;
	package->package_string[5] = package->address;

	package->package_string[6] = package->pid;

	package->package_string[7] = package->length >> 8;
	package->package_string[8] = package->length;

	for (i = 0; i < package->data_size; i++) {
		package->package_string[i + 9] = package->data[package->length
				- sizeof(package->checksum) - 1 - i];
	}

	package->package_string[i + 9] = package->checksum >> 8;
	package->package_string[i + 10] = package->checksum;
	return package->package_string;
}

/**
 * @brief Load complete data_package structure from byte string.
 * @param package_string Input byte string.
 * @param package Pointer to data_package to load.
 * @return
 * 			-1: if checksum match.
 * 			-0: if checksum mismatch.
 */
uint8_t loadPackage(uint8_t* package_string, data_package *package) {
	uint16_t i = 0;
	package->header = (uint16_t) package_string[0] << 8
			| (uint16_t) package_string[1];
	package->address = (uint32_t) package_string[2] << 8 * 3
			| (uint32_t) package_string[3] << 8 * 2
			| (uint32_t) package_string[4] << 8 * 1
			| (uint32_t) package_string[5];
	package->pid = (uint8_t) package_string[6];
	package->length = (uint16_t) package_string[7] << 8
			| (uint16_t) package_string[8];

	package->data_size = package->length - sizeof(package->checksum);

	for (i = 0; i < package->data_size; i++) {
		//UART reads Highest byte first
		// package->length - sizeof(package->checksum) -1 to get the highest byte
		package->data[package->data_size - 1 - i] = package_string[9 + i];
	}
	autoSetChecksum(package);
	autoSetPackageSize(package);
	// Copy string
	for (i = 0; i < package->package_size; i++) {
		package->package_string[i] = package_string[i];
	}

	package->ack_command_code = package->data[package->data_size];

	if (((uint16_t) package_string[9 + i] << 8
			| (uint16_t) package_string[10 + i]) != package->checksum) {
		return 0; // Checksum doesn't match
	} else {
		return 1;	// Checksum match
	}

}

/**
 * @fn void Write_fn(uint8_t* str,uint32_t size)
 * @brief callback function to write byte string.
 * @param str byte string to send. data_package::package_string is passed
 * @param size size of byte string. data_package::package_size is passed
 */

/**
 * @brief Send data_package using callback function Write_fn.
 * @param package data_package to be sent.
 * @param Write_fn callback function
 *
 */
// The argument Write_fn should be a function with arguments (uint8_t*,uint32_t) of which
// First argument is array of bytes to be sent using that function.
// Second argument is the size of the array.
void sendPackage(data_package *package, void (*Write_fn)(uint8_t*, uint32_t)) {
	autoSetChecksum(package);
	autoSetPackageSize(package);
	Write_fn(package->package_string, package->package_size);
}

/**
 * @brief
 * @param package data_package to load received data.
 * @param size No. of bytes to receive. For most of ACK package use LEN_ACK* + 9.
 * @param Read_fn callback function to read data bytes.
 * @return
 * 			1: for valid package.
 * 			0: for invalid package.
 * @sa \link LengthACK \endlink
 */
// The argument Read_fn should be a function with arguments (uint8_t*,uint32_t) of which
// First argument is array of bytes to be received using that function
// Second argument is the size of the array.
int recvPackage(data_package *package, uint16_t size,
		void (*Read_fn)(uint8_t*, uint32_t)) {
	uint8_t tmp_package_string[256];
	Read_fn(tmp_package_string, (uint32_t) size);
	return loadPackage(tmp_package_string, package);
}
