
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
#define COMMAND_PACKAGE	0x01
#define DATA_PACKAGE 	0x02
#define ACK_PACKAGE		0x07
#define EOD_PACKAGE		0x08

// ACK bytecode definition
#define ACK_COMMAND_EXEC_COMPLETE		0X00
#define	ACK_ERROR_RECEIVING_DATA		0X01
#define	ACK_NO_FINGER_ON_SENSOR			0X02
#define ACK_FAIL_TO_ENROLL_FINGER		0X03
#define ACK_CHAR_FILE_FAIL_OVERDISORDER	0X06
#define ACK_CHAR_FILE_FAIL_LESS_POINTS	0X07
#define ACK_FINGER_DOESNT_MATCH			0X08
#define ACK_FAIL_TO_COMBINE				0X0A
#define ACK_ADDRESS_BEYOND_RANGE		0X0B
#define ACK_ERROR_READING_TEMPLATE		0X0C
#define ACK_ERROR_UPLOADING_TEMPLATE	0X0D
#define ACK_CANT_RECIVE_DATA_PACKAGE	0X0E
#define ACK_ERROR_UPLOADING_IMAGE		0X0F
#define ACK_FAIL_DELETE_TEMPLATE		0X10
#define ACK_FAIL_CLEAR_LIBRARY			0X11
#define ACK_WRONG_PWD					0x13
#define ACK_FAIL_TO_GENERATE_IMAGE		0X15
#define ACK_ERROR_WRITING_FLASH			0X18
#define ACK_NO_DEFINITION_ERROR			0X19
#define ACK_INVALID_REG_NO				0X1A
#define ACK_INCORRECT_REG_CONFIG		0X1B
#define ACK_WRONG_PAGE_NO				0X1C
#define ACK_COM_PORT_FALIURE			0x1D

// Defaults
#define	DEFAULT_ADDRESS		0xFFFFFFFF
#define DEFAULT_PWD			0xFFFFFFFF
#define DEFAULT_HEADER		0xEF01

// Standard Package Length Parameter

// For Command package
#define	LEN_COMMAND_GEN_IMG			0X0003
#define	LEN_COMMAND_IMG2TZ			0X0004
#define	LEN_COMMAND_MATCH			0X0003
#define	LEN_COMMAND_SEARCH			0X0008
#define	LEN_COMMAND_REG_MODEL		0X0003
#define	LEN_COMMAND_STORE			0X0006
#define	LEN_COMMAND_LOAD_CHAR		0X0006
#define	LEN_COMMAND_UP_CHAR			0X0004
#define	LEN_COMMAND_DOWN_CHAR		0X0004
#define	LEN_COMMAND_UP_IMAGE		0X0003
#define	LEN_COMMAND_DOWN_IMAGE		0X0003
#define	LEN_COMMAND_DELETE_CHAR		0X0007
#define	LEN_COMMAND_EMPTY			0X0003
//#define	LEN_COMMAND_SET_SYS_PARA	0X00; Variable size 4/5/6
#define	LEN_COMMAND_READ_SYS_PARA	0X0003
#define	LEN_COMMAND_SET_PWD			0X0007
#define	LEN_COMMAND_VFY_PWD			0X0007
#define	LEN_COMMAND_GET_RANDOM_CODE	0X0003
#define	LEN_COMMAND_SET_ADDER		0X0007
#define	LEN_COMMAND_CONTROL			0X0004
#define	LEN_COMMAND_WRITE_NOTEPAD	0X0024
#define	LEN_COMMAND_READ_NOTEPAD	0X0004
//#define	LEN_COMMAND_HI_SPEED_SEARCH	0X00; Not in datasheet
#define	LEN_COMMAND_TEMPLETE_NUM	0X0003

// For Acknowledge	package
#define	LEN_ACK_GEN_IMG			0X0003
#define	LEN_ACK_IMG2TZ			0X0003
#define	LEN_ACK_MATCH			0X0005
#define	LEN_ACK_SEARCH			0X0007
#define	LEN_ACK_REG_MODEL		0X0003
#define	LEN_ACK_STORE			0X0007
#define	LEN_ACK_LOAD_CHAR		0X0007
#define	LEN_ACK_UP_CHAR			0X0003
#define	LEN_ACK_DOWN_CHAR		0X0003
#define	LEN_ACK_UP_IMAGE		0X0003
#define	LEN_ACK_DOWN_IMAGE		0X0003
#define	LEN_ACK_DELETE_CHAR		0X0003
#define	LEN_ACK_EMPTY			0X0003
#define	LEN_ACK_SET_SYS_PARA	0X0003
#define	LEN_ACK_READ_SYS_PARA	0X0013
#define	LEN_ACK_SET_PWD			0X0003
#define	LEN_ACK_VFY_PWD			0X0003
#define	LEN_ACK_GET_RANDOM_CODE	0X0007
#define	LEN_ACK_SET_ADDER		0X0007
#define	LEN_ACK_CONTROL			0X0003
#define	LEN_ACK_WRITE_NOTEPAD	0X0003
#define	LEN_ACK_READ_NOTEPAD	0X0023
//#define	LEN_ACK_HI_SPEED_SEARCH	0X00; Not in datasheet
#define	LEN_ACK_TEMPLETE_NUM	0X0005
//......

// Instruction Codes
#define	COMMAND_GEN_IMG			0X01
#define	COMMAND_IMG2TZ			0X02
#define	COMMAND_MATCH			0X03
#define	COMMAND_SEARCH 			0X04
#define	COMMAND_REG_MODEL 		0X05	
#define	COMMAND_STORE 			0X06
#define	COMMAND_LOAD_CHAR 		0X07
#define	COMMAND_UP_CHAR			0X08
#define	COMMAND_DOWN_CHAR		0X09
#define	COMMAND_UP_IMAGE		0X0A
#define	COMMAND_DOWN_IMAGE		0X0B
#define	COMMAND_DELETE_CHAR		0X0C
#define	COMMAND_EMPTY			0X0D
#define	COMMAND_SET_SYS_PARA	0X0E
#define	COMMAND_READ_SYS_PARA	0X0F
#define	COMMAND_SET_PWD			0X12
#define	COMMAND_VFY_PWD			0X13
#define	COMMAND_GET_RANDOM_CODE	0X14	
#define	COMMAND_SET_ADDER		0X15
#define	COMMAND_CONTROL			0X17
#define	COMMAND_WRITE_NOTEPAD	0X18	
#define	COMMAND_READ_NOTEPAD	0X19	
#define	COMMAND_HI_SPEED_SEARCH	0X1B
#define	COMMAND_TEMPLETE_NUM	0X1D

typedef struct {
	//package data
	uint16_t header;
	uint32_t address;
	uint8_t pid;
	uint16_t length;
	uint8_t data[256];
	uint16_t checksum;
	//Helper data
	uint16_t package_size;
	uint8_t package_string[256];
	uint8_t ack_command_code;
	uint8_t data_size;
} data_package;

data_package getBasePackage(uint8_t, uint16_t, uint8_t*);
data_package getEmptyPackage(uint8_t);
data_package getAckPackage();
data_package getCommandPackage(uint16_t, uint8_t*);
uint16_t setChecksum(data_package*);
uint32_t setPackageSize(data_package*);
uint8_t* stringyfyPackage(data_package*);
uint8_t loadPackage(uint8_t*, data_package*);
void sendPackage(data_package *, void (*Write_fn)(uint8_t*, uint32_t));
int recvPackage(data_package *, uint16_t, void (*Read_Fn)(uint8_t*, uint32_t));
