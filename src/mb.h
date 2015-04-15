/**
***********************************************************
* @name mb.c
* @brief ModBus
*
***********************************************************
*/
#ifndef _MB_H_
#define _MB_H_
#include <stdint.h>

/* This MB object */
struct modbus_ascii;

/**
* @brief Init MB 
*/
void modbus_ascii_init(struct modbus_ascii*);

/**
* @brief Receive new byte
* @param received byte
*/
void modbus_ascii_rec_byte(struct modbus_ascii* mb, uint8_t byte);

/**
* @brief Reset Modbus state(e.g. timeout, error or any reason)
**/
void modbus_ascii_rst(struct modbus_ascii* mb);

#endif	/* _MB_H_ */
