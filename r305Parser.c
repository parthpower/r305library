#include "r305Parser.h"

data_package getBasePackage(uint8_t pid, uint16_t length, uint8_t* data) {
	uint16_t i = 0;

	data_package package = getEmptyPackage(pid);
	package.length = length;
	package.data_size = package.length - sizeof(package.checksum);
	for (i = 0; i < package.data_size; i++) {
		package.data[package.data_size - i - 1] = data[i];
	}
	setChecksum(&package);
	setPackageSize(&package);
	stringyfyPackage(&package);
	package.ack_command_code = package.data[package.data_size];

	return package;
}

data_package getEmptyPackage(uint8_t pid) {
	data_package package;
	package.header = DEFAULT_HEADER;
	package.address = DEFAULT_ADDRESS;
	package.pid = pid;
	return package;
}

inline data_package getAckPackage() {
	return getEmptyPackage(ACK_PACKAGE);
}

inline data_package getCommandPackage(uint16_t length, uint8_t* data) {
	return getBasePackage(COMMAND_PACKAGE, length, data);

}

uint16_t setChecksum(data_package *package) {
	uint16_t i = 0;
	package->checksum = (uint16_t) package->pid + (uint16_t) package->length;
	for (i = 0; i < package->length - sizeof(package->checksum); i++) {
		package->checksum += (uint16_t) package->data[i];
	}
	return package->checksum;
}

uint32_t setPackageSize(data_package *package) {
	package->package_size = sizeof(package->header) + sizeof(package->address)
			+ sizeof(package->pid) + sizeof(package->length) + package->length;
	return package->package_size;
}

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
// Argument: data_package *package is the output 
// Must call it as loadPackage(someBuffer,&receivedPackage)
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

	for (i = 0; i < package->length; i++) {
		//UART reads Highest byte first
		// package->length - sizeof(package->checksum) -1 to get the highest byte
		package->data[package->length - sizeof(package->checksum) - 1 - i] =
				package_string[9 + i];
	}
	setChecksum(package);
	setPackageSize(package);
	stringyfyPackage(package); //Maybe use strcpy here
	package->data_size = package->length - sizeof(package->checksum);
	package->ack_command_code = package->data[package->data_size];

	if (((uint16_t) package_string[9 + i] << 8
			| (uint16_t) package_string[10 + i]) != package->checksum) {
		return 0;
	} else {
		return 1;
	}

}

void sendPackage(data_package *package, void (*Write_fn)(uint8_t*, uint32_t)) {
	setChecksum(package);
	setPackageSize(package);
	Write_fn(package->package_string, package->package_size);
}

int recvPackage(data_package *package, uint16_t size,
		void (*Read_fn)(uint8_t*, uint32_t)) {
	uint8_t tmp_package_string[256];
	Read_fn(tmp_package_string, (uint32_t) size);
	return loadPackage(tmp_package_string, package);
}
