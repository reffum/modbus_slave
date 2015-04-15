/**
* gpio.h
* Input/output ports
*
*/
#ifndef _GPIO_H_
#define _GPIO_H_
#include <stdbool.h>

/* Инициализация портов ввода/вывода */
void gpio_init(void);

/* Линии управления питанием */
void pow_9_9V_on(void);
void pow_9_9V_off(void);
void pow_5_6V_on(void);
void pow_5_6V_off(void);
void pow_5_6V_bpog_on(void);
void pow_5_6V_bpog_off(void);
void pow_m5_6V_on(void);
void pow_m5_6V_off(void);
void pow_3_9V_on(void);
void pow_3_9V_off(void);
void led_on(unsigned n);
void led_off(unsigned n);
void led_all_off(void);
void led_all_on(void);
void set_sw_out(bool b);
void shdn_3_3_gen(bool b);
void shdn_3_3_clk(bool b);
void shdn_7_bpog_on(void);
void shdn_7_bpog_off(void);
void set_adclk_control(bool b);
void set_ou_pd1(bool b);
void set_ou_pd2(bool b);
void reset(bool b);
bool get_achtung(void);

void set_usart_tx(void);
void set_usart_rx(void);

/**
* @brief Направление приема/передачи
* @retval true - TX
*/
bool get_usart_dir(void);

#define LED_COUNT			6
#define LED_12V_FAIL		0
#define LED_9V9_FAIL		1
#define LED_5V6_FAIL		2
#define LED_3V9_FAIL		3
#define LED_POWER_ON		5
#define LED_REF_OUT			4

#endif
