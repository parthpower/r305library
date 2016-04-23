#include <stdio.h>
#include "r305Parser.h"
void printFn(uint8_t* str, uint32_t size) {
	uint32_t var;
	for (var = 0; var < size; ++var) {
		printf("%x ", str[var]);
	}
}

int main(int argc, char const *argv[]) {
	int i;
	data_package txPackage;
	uint8_t tmp[] = { COMMAND_VFY_PWD, 0xff, 0xff, 0xff, 0xff };
	txPackage = getCommandPackage(LEN_COMMAND_VFY_PWD, tmp);
	for (i = 0; i < txPackage.package_size; i++) {
		printf("%x ", txPackage.package_string[i]);
	}
	printf("\n");
	sendPackage(&txPackage, printFn);
	return 0;
}
