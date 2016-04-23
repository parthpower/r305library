#include <stdio.h>
#include <stdlib.h>
#include "r305Parser.h"

data_package txPackage;

void printFn(uint8_t* str, uint32_t size) {
	uint32_t var;
	for (var = 0; var < size; ++var) {
		printf("%.2x ", str[var]);
	}
}

void scanFn(uint8_t *str,uint32_t size){
	int var;
	for (var = 0; var < size; ++var) {
		str[var] = txPackage.package_string[var];
	}
}

int main(int argc, char const *argv[]) {
	int i;
	data_package rxPackage;
	uint8_t tmp[] = {COMMAND_VFY_PWD, 0xff, 0xff, 0xff, 0xff };
	txPackage = getCommandPackage(LEN_COMMAND_VFY_PWD, tmp);
	printf("Test Pass if all the outputs from below looks the exact same\n");
	for (i = 0; i < txPackage.package_size; i++) {
		printf("%.2x ", txPackage.package_string[i]);
	}
	printf("\n");
	sendPackage(&txPackage, printFn);
	fflush(stdout);
	recvPackage(&rxPackage,txPackage.package_size,scanFn);
	printf("\n");
	sendPackage(&rxPackage,printFn);
	return 0;
}
