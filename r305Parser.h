/**
 * \file
 * \brief Header for r305Parser
 *
 */
// Typedefs for uint* types
//typedef unsigned char uint8_t;
//typedef unsigned short int uint16_t;
//typedef unsigned int uint32_t;
#include <inttypes.h>

/**
 * \addtogroup DefaultSettings
 * \brief Default settings of r305 module
 * @{
 */

// Default settings
#define	DEFAULT_ADDRESS		0xFFFFFFFF	///<Default address
#define DEFAULT_PWD			0xFFFFFFFF	///<Default password
#define DEFAULT_HEADER		0xEF01		///<Default header
/**@}*/
/**
 * \addtogroup PID
 * \brief PID for the package types
 * @{
 */
// Package types PID
#define COMMAND_PACKAGE	0x01
#define DATA_PACKAGE 	0x02
#define ACK_PACKAGE		0x07
#define EOD_PACKAGE		0x08
/**@} */

/**
 * \addtogroup ACKErrorCodes
 * \brief Error codes for ACK packages.
 * @{
 */
// ACK error code definition
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
/**@} */
// Standard Package Length Parameter
/**
 * \addtogroup Length
 * \brief Standard Package Lengths
 * @{
 */
// For Command package
/**
 * \addtogroup LengthCommand
 * \brief Lengths of Command Packages
 * @{
 */
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
/**@} */

/**
 * \addtogroup LengthACK
 * \brief Lengths of ACK packages.
 * @{
 */
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
/**@} */
/**@} */
// Instruction Codes
/**
 *	\addtogroup InstructionCodes
 *	\brief Command Codes
 *	@{
 */
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
/**
 *@}
 */
/**
 * \struct data_package
 * \brief Package structure
 */
typedef struct data_package {
	uint16_t header; ///<Header of Package. Default value define \link DEFAULT_HEADER \endlink
	uint32_t address;	///<Address of the module
	uint8_t pid;///<PID of package to determine type of package use \link PID \endlink
	uint16_t length;///<length of data+checksum (length parameter) use \link Length \endlink
	uint8_t data[256];	///<data of the package
	uint16_t checksum;	///<checksum

	uint16_t package_size; ///<Total count of bytes in a package
	uint8_t package_string[256]; ///<Package in from array of bytes (Most significant byte first)
	uint8_t ack_command_code;	///<Command or ACK code
	uint8_t data_size;			///<Size of data in a package
} data_package;

data_package getBasePackage(uint8_t pid, uint16_t length, uint8_t* data); // Arguments are PID, length,data array

data_package getDefaultPackage(uint8_t pid);//Returns package with specified PID

data_package getAckPackage();//Returns default package with PID 0x07 for ACK package (can be useful for emulation)
data_package getCommandPackage(uint16_t length, uint8_t* data);
//Returns default package with PID 0x01 for command package
//first argument is for length parameter look for LEN_COMMAND_*

uint16_t autoSetChecksum(data_package *package);//Sets the checksum parameter of the package and returns the checksum
uint32_t autoSetPackageSize(data_package *package);	//Sets the package_size parameter of the package and returns the size of the package string
uint8_t* stringyfyPackage(data_package *package);//Sets the package_string parameter of the package and return the byte string of the whole package
uint8_t loadPackage(uint8_t *package_string, data_package *package);//load package structure from string.

void sendPackage(data_package *package, void (*Write_fn)(uint8_t*, uint32_t));
// The argument Write_fn should be a function with arguments (uint8_t*,uint32_t) of which
// First argument is array of bytes to be sent using that function.
// Second argument is the size of the array.

int recvPackage(data_package *package, uint16_t,
		void (*Read_Fn)(uint8_t*, uint32_t));
// The argument Read_fn should be a function with arguments (uint8_t*,uint32_t) of which
// First argument is array of bytes to be received using that function
// Second argument is the size of the array.
