/**
***********************************************************************
* @file mb_functions.h
* @brief Modbus functions description
* @author  Gavrilchenko Oleg
* @e-main Gavrilchenko@avionica.spb.ru
***********************************************************************
**/
#ifndef _MB_FUNCTIONS_H_
#define _MB_FUNCTIONS_H_

#define MODBUS_FUNCTION_NUM  127

/* Function codes */
#define MB_READ_HOLD			0x03
#define MB_WRITE_SINGLE			0x06
#define MB_EXCEPTION			0x81

/* Exception codes */
#define MB_ILLEGAL_FUNCTION		0x01
#define MB_ILLEGAL_DATA_ADDRESS		0x02

/**
* @brief Read hold function handler prototipe
* @addr Start addres
* @len  Number of registers
* @out_buffer buffer for registers values
* @retval 0 - if SUCCES, other error code 
**/
typedef int(*read_hold_handler)(
	uint16_t addr, 
	uint16_t len, 
	uint16_t * out_buffer);
	
/**
* @brief Write single function hanlder
* @addr 
* @value
* @retval 0 - SUCCESS, Ohter - exception code
**/
typedef int(*write_single_handler)(
	uint16_t addr,
	uint16_t *value);

	


#endif	/* _MB_FUNCTIONS_H_ */
