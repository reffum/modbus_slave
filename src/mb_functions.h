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

const int MODBUS_FUNCTION_NUM 	= 127;

/* Function codes */
#define MB_READ_HOLD			0x03
#define MB_WRITE_HOLD			0x06

/* Exception codes */
#define MB_ILLEGAL_FUNCTION		0x01


#endif	/* _MB_FUNCTIONS_H_ */
