/*
 * timer.h
 * ������ ��� ���������� 
 * ������ �������� 
 */

#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdbool.h>
#include <stdint.h>

void timer_init(void);

/* ��������� ������� */
void timer_100ns_set(int tm, uint32_t interval);
void timer_us_set(int tm, uint32_t interval);
void timer_ms_set(int tm, uint32_t interval);

/* �������� ������� */
bool timer_complete(int tm);

/* ������� ���������� �������� */
void delay_100ns(uint32_t intv);
void delay_s(uint32_t interval);
void delay_ms(uint32_t interval);
void delay_us(uint32_t interval);

/* ����������� �������� */
#define I2C_TIMER				0
#define TIMERS_NUM			1

#endif	/* _TIMER_H_	*/
