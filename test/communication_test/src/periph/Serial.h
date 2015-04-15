/**
* serial.c
* �������� �� ������ � ���������������� ������ �� ���������� RS-485
*
*
*/

#ifndef __SERIAL_H
#define __SERIAL_H

/**
* @breif ������������� USART
*/
void Serial_Init(void);

/**
* @brief �������� ������ �� RS-485
*/
void Serial_send_bytes(uint8_t* data, int len);

#endif  /* __SERIAL_H */
