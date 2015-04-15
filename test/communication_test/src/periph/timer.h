/*
 * timer.h
 * Таймер для реализации 
 * точных задержек 
 */

#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdbool.h>
#include <stdint.h>

void timer_init(void);

/* Установка таймера */
void timer_100ns_set(int tm, uint32_t interval);
void timer_us_set(int tm, uint32_t interval);
void timer_ms_set(int tm, uint32_t interval);

/* Проверка таймера */
bool timer_complete(int tm);

/* Функции синхронных задержек */
void delay_100ns(uint32_t intv);
void delay_s(uint32_t interval);
void delay_ms(uint32_t interval);
void delay_us(uint32_t interval);

/* Определения таймеров */
#define I2C_TIMER				0
#define TIMERS_NUM			1

#endif	/* _TIMER_H_	*/
