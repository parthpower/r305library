#include <avr/io.h>
#include <inttypes.h>
#include "r305Parser.h"
void UARTInit(uint16_t ubrr_value);
uint8_t UARTReadChar();
void UARTWriteChar(uint8_t data);
void UARTReadStr(uint8_t *buffer, uint32_t size);
void UARTWriteStr(uint8_t* buffer, uint32_t size);

void UARTInit(uint16_t ubrr_value) {

	//Set Baud rate
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >> 8);
	/*Set Frame Format
	 >> Asynchronous mode
	 >> No Parity
	 >> 1 StopBit
	 >> char size 8
	 */
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
	//Enable The receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);
}

uint8_t UARTReadChar() {
	while (!(UCSRA & (1 << RXC)))
		;
	return UDR;
}

void UARTWriteChar(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

void UARTReadStr(uint8_t *buffer, uint32_t size) {
	uint32_t i = 0;
	for (i = 0; i < size; i++) {
		buffer[i] = UARTReadChar();
	}
}

void UARTWriteStr(uint8_t* buffer, uint32_t size) {
	uint32_t i = 0;
	for (i = 0; i < size; i++) {
		UARTWriteChar(buffer[i]);
	}
}

int main() {
	data_package rxPackage, txPacakage;
	//for verify pwd
	unsigned char vfyPwdFormat[] = { COMMAND_VFY_PWD, 0xff, 0xff, 0xff, 0xff };
	getBasePackage(&txPacakage, COMMAND_PACKAGE, LEN_COMMAND_VFY_PWD,
			vfyPwdFormat);

	UARTInit(8); //UBRR = idk what's the exact value just calculate and do, it's 12 I think
	PORTA = 0xff;

	while (1) {
		sendPackage(&txPacakage, UARTWriteStr);
		recvPackage(&rxPackage, LEN_ACK_VFY_PWD + 9, UARTReadStr); //receive length of data + 9 (extra bytes) from UART
		if (rxPackage.ack_command_code == ACK_COMMAND_EXEC_COMPLETE) {
			//This means ACK sucessful :)
			// DO SOMETHING HERE TO SHOW SUCESS
			PORTA = 0x10;
		} else {
			PORTA = 0x20;
		}

	}
	return 0;
}
