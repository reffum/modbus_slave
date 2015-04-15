/**
* serial.c
* Отвечает за работу с последовательным портом по интерфейсу RS-485
*
*
*/

#ifndef __SERIAL_H
#define __SERIAL_H

/**
* @breif Инициализация USART
*/
void Serial_Init(void);

/**
* @brief Посылает данные по RS-485
*/
void Serial_send_bytes(uint8_t* data, int len);

#endif  /* __SERIAL_H */
