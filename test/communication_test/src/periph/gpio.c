/**
* gpio.c
* Управление линиями ввода-вывода
*/
#include <stdbool.h>
#include <stm32f4xx.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "gpio.h"

//A
#define LED6_bit						0
#define LED5_bit						1
#define SW_CONTROL_bit					2
#define SHDN_56_BPOG_bit				4
#define PG_56_BPOG_bit					5
#define PG_39_BPOG_bit					6
#define DET_OUT100_bit					7
#define TSCL_bit						8
//B
#define LED1_bit						0
#define LED2_bit						1
#define LED3_bit						2
#define LED4_bit						10
#define PG_39_bit						13
#define SHDN_39_bit						14
#define SHDN_56_bit						15
//C
#define SHDN_M56_bit					1
#define PG_56_bit						6
#define SHDN_99_BKCH_bit				8
#define TSDA_bit						9
#define DE_RE_bit						12

#define HI(p,x) p->ODR |= (1UL<<x)
#define LO(p,x) p->ODR &= ~(1UL<<x)

void gpio_init()
{	
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIOA->MODER   &= ~(
											(3UL<<2*LED6_bit)|
											(3UL<<2*LED5_bit)|
											(3UL<<2*SW_CONTROL_bit)|
											(3UL<<2*SHDN_56_BPOG_bit)|
											(0UL<<2*PG_56_BPOG_bit)|
											(0UL<<2*PG_39_BPOG_bit)|
											(3UL<<2*DET_OUT100_bit)
											);
	GPIOA->MODER   |=  (
											(1UL<<2*LED6_bit)|
											(1UL<<2*LED5_bit)|
											(1UL<<2*SW_CONTROL_bit)|
											(1UL<<2*SHDN_56_BPOG_bit)|
											(1UL<<2*PG_56_BPOG_bit)|
											(1UL<<2*PG_39_BPOG_bit)|
											(3UL<<2*DET_OUT100_bit)
											);
	GPIOA->OTYPER  &= ~(
											(1UL<<LED6_bit)|
											(1UL<<LED5_bit)|
											(1UL<<SW_CONTROL_bit)|
											(1UL<<SHDN_56_BPOG_bit)|
											(1UL<<PG_56_BPOG_bit)|
											(1UL<<PG_39_BPOG_bit)|
											(1UL<<DET_OUT100_bit)
											);
	GPIOA->OSPEEDR &= ~(
											(3UL<<2*LED6_bit)|
											(3UL<<2*LED5_bit)|
											(3UL<<2*SW_CONTROL_bit)|
											(3UL<<2*SHDN_56_BPOG_bit)|
											(3UL<<2*PG_56_BPOG_bit)|
											(3UL<<2*PG_39_BPOG_bit)|
											(3UL<<2*DET_OUT100_bit)
											);
	GPIOA->OSPEEDR |=  (
											(2UL<<2*LED6_bit)|
											(2UL<<2*LED5_bit)|
											(2UL<<2*SW_CONTROL_bit)|
											(2UL<<2*SHDN_56_BPOG_bit)|
											(2UL<<2*PG_56_BPOG_bit)|
											(2UL<<2*PG_39_BPOG_bit)|
											(2UL<<2*DET_OUT100_bit)
											);
	GPIOA->PUPDR   &= ~(
											(3UL<<2*LED6_bit)|
											(3UL<<2*LED5_bit)|
											(3UL<<2*SW_CONTROL_bit)|
											(3UL<<2*SHDN_56_BPOG_bit)|
											(3UL<<2*PG_56_BPOG_bit)|
											(3UL<<2*PG_39_BPOG_bit)|
											(3UL<<2*DET_OUT100_bit)
											);
	GPIOA->PUPDR   |=  (
											(1UL<<2*LED6_bit)|
											(1UL<<2*LED5_bit)|
											(1UL<<2*SW_CONTROL_bit)|
											(1UL<<2*SHDN_56_BPOG_bit)|
											(1UL<<2*PG_56_BPOG_bit)|
											(1UL<<2*PG_39_BPOG_bit)|
											(1UL<<2*DET_OUT100_bit)
											);

	GPIOB->MODER   &= ~(
											(3UL<<2*LED1_bit)|
											(3UL<<2*LED2_bit)|
											(3UL<<2*LED3_bit)|
											(3UL<<2*LED4_bit)|
											(0UL<<2*PG_39_bit)|
											(3UL<<2*SHDN_39_bit)|
											(3UL<<2*SHDN_56_bit)
											);
	GPIOB->MODER   |=  (
											(1UL<<2*LED1_bit)|
											(1UL<<2*LED2_bit)|
											(1UL<<2*LED3_bit)|
											(1UL<<2*LED4_bit)|
											(1UL<<2*PG_39_bit)|
											(1UL<<2*SHDN_39_bit)|
											(1UL<<2*SHDN_56_bit)
											);
	GPIOB->OTYPER  &= ~(
											(1UL<<LED1_bit)|
											(1UL<<LED2_bit)|
											(1UL<<LED3_bit)|
											(1UL<<LED4_bit)|
											(1UL<<PG_39_bit)|
											(1UL<<SHDN_39_bit)|
											(1UL<<SHDN_56_bit)
											);
	GPIOB->OSPEEDR &= ~(
											(3UL<<2*LED1_bit)|
											(3UL<<2*LED2_bit)|
											(3UL<<2*LED3_bit)|
											(3UL<<2*LED4_bit)|
											(3UL<<2*PG_39_bit)|
											(3UL<<2*SHDN_39_bit)|
											(3UL<<2*SHDN_56_bit)
											);
	GPIOB->OSPEEDR |=  (
											(2UL<<2*LED1_bit)|
											(2UL<<2*LED2_bit)|
											(2UL<<2*LED3_bit)|
											(2UL<<2*LED4_bit)|
											(2UL<<2*PG_39_bit)|
											(2UL<<2*SHDN_39_bit)|
											(2UL<<2*SHDN_56_bit)
											);
	GPIOB->PUPDR   &= ~(
											(3UL<<2*LED1_bit)|
											(3UL<<2*LED2_bit)|
											(3UL<<2*LED3_bit)|
											(3UL<<2*LED4_bit)|
											(3UL<<2*PG_39_bit)|
											(3UL<<2*SHDN_39_bit)|
											(3UL<<2*SHDN_56_bit)
											);
	GPIOB->PUPDR   |=  (
											(1UL<<2*LED1_bit)|
											(1UL<<2*LED2_bit)|
											(1UL<<2*LED3_bit)|
											(1UL<<2*LED4_bit)|
											(1UL<<2*PG_39_bit)|
											(1UL<<2*SHDN_39_bit)|
											(1UL<<2*SHDN_56_bit)
											);

	GPIOC->MODER   &= ~(
											(3UL<<2*SHDN_M56_bit)|
											(0UL<<2*PG_56_bit)|
											(3UL<<2*SHDN_99_BKCH_bit)|
											(3UL<<2*DE_RE_bit)
											);
	GPIOC->MODER   |=  (
											(1UL<<2*SHDN_M56_bit)|
											(1UL<<2*PG_56_bit)|
											(1UL<<2*SHDN_99_BKCH_bit)|
											(1UL<<2*DE_RE_bit)
											);
	GPIOC->OTYPER  &= ~(
											(1UL<<SHDN_M56_bit)|
											(1UL<<PG_56_bit)|
											(1UL<<SHDN_99_BKCH_bit)|
											(1UL<<DE_RE_bit)
											);
	GPIOC->OSPEEDR &= ~(
											(3UL<<2*SHDN_M56_bit)|
											(3UL<<2*PG_56_bit)|
											(3UL<<2*SHDN_99_BKCH_bit)|
											(3UL<<2*DE_RE_bit)											
											);
	GPIOC->OSPEEDR |=  (
											(2UL<<2*SHDN_M56_bit)|
											(2UL<<2*PG_56_bit)|
											(2UL<<2*SHDN_99_BKCH_bit)|
											(2UL<<2*DE_RE_bit)
											);
  GPIOC->PUPDR   &= ~(
											(3UL<<2*SHDN_M56_bit)|
											(3UL<<2*PG_56_bit)|
											(3UL<<2*SHDN_99_BKCH_bit)|
											(3UL<<2*DE_RE_bit)
											);
  GPIOC->PUPDR   |=  (
											(1UL<<2*SHDN_M56_bit)|
											(1UL<<2*PG_56_bit)|
											(1UL<<2*SHDN_99_BKCH_bit)|
											(1UL<<2*DE_RE_bit)
											);
	// PA OUT 
	gpio.GPIO_Pin = GPIO_Pin_3 ;			// SHDN_33_CLK					
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpio);
	
	// PB IN	
	gpio.GPIO_Pin = GPIO_Pin_5;			// ACHTUNG
	gpio.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB, &gpio);	
		
	// PB OUT	
	gpio.GPIO_Pin = GPIO_Pin_12;			// OU_PD2
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &gpio);
		
	// PC OUT
	gpio.GPIO_Pin = GPIO_Pin_2 |			// OU_PD1
					GPIO_Pin_3 |			// SHDN_3.3V_gen
					GPIO_Pin_4 |			// SHDN_7_BPOG					
					GPIO_Pin_15;			// ADCLK_control
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpio);	
	
	// PC Open drain
	gpio.GPIO_Pin = GPIO_Pin_0;				// ~Reset
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpio);		
		
	/* I2C I/O configuration 
	 */
	GPIOA->AFR[0] &= ~0x00000000;  GPIOA->AFR[1] &= ~0x0000000F; 
	GPIOA->AFR[0] |=  0x00000000;  GPIOA->AFR[1] |=  0x00000004; 
	GPIOC->AFR[0] &= ~0x00000000;  GPIOC->AFR[1] &= ~0x000000F0; 
	GPIOC->AFR[0] |=  0x00000000;  GPIOC->AFR[1] |=  0x00000040; 

	GPIOA->MODER &= ~( (3UL << 2*TSCL_bit)  );
	GPIOA->MODER |= ( (2UL << 2*TSCL_bit)  );
	GPIOA->OTYPER |= ( (1UL<< TSCL_bit )  );
	GPIOA->OSPEEDR &= ~( (3UL<< 2*TSCL_bit )  );
	GPIOA->OSPEEDR |= ( (1UL<< 2*TSCL_bit )  );
	GPIOA->PUPDR &= ~( (3UL<< 2*TSCL_bit )  );
	GPIOA->PUPDR |= ( (1UL<< 2*TSCL_bit )  );

	GPIOC->MODER &= ~(  (3UL << 2*TSDA_bit) );
	GPIOC->MODER |= (  (2UL << 2*TSDA_bit) );
	GPIOC->OTYPER |= (  (1UL<< TSDA_bit) );
	GPIOC->OSPEEDR &= ~(  (3UL<< 2*TSDA_bit) );
	GPIOC->OSPEEDR |= (  (1UL<< 2*TSDA_bit) );
	GPIOC->PUPDR &= ~(  (3UL<< 2*TSDA_bit) );
	GPIOC->PUPDR |= (  (1UL<< 2*TSDA_bit) );	

	/* UART3 I/O configuration
	 */
	GPIOC->MODER &= ~( (3UL << 2*10) | (3UL << 2*11) );
	GPIOC->MODER |= ( (2UL << 2*10) | (2UL << 2*11) );
	GPIOC->AFR[0] &= ~0x0000FF00;
	GPIOC->AFR[1] |=  0x00007700;

	GPIOC->PUPDR |= (1UL << 2 *10) | (1UL << 2 *11);
}

/* Линии управления питанием */
void pow_9_9V_on(void)
{
	HI(GPIOC, SHDN_99_BKCH_bit);
}
void pow_9_9V_off(void)
{
	LO(GPIOC, SHDN_99_BKCH_bit);
}

void pow_5_6V_on(void)
{
	HI(GPIOB, SHDN_56_bit);
}

void pow_5_6V_off(void)
{
	LO(GPIOB, SHDN_56_bit);
}

void pow_5_6V_bpog_on(void)
{
	HI(GPIOA, SHDN_56_BPOG_bit);
}

void pow_5_6V_bpog_off(void)
{
	LO(GPIOA, SHDN_56_BPOG_bit);
}

void pow_m5_6V_on(void)
{
	HI(GPIOC, SHDN_M56_bit);
}
void pow_m5_6V_off(void)
{
	LO(GPIOC, SHDN_M56_bit);
}

void pow_3_9V_on(void)
{
	HI(GPIOB, SHDN_39_bit);
}
void pow_3_9V_off(void)
{
	LO(GPIOB, SHDN_39_bit);
}

void shdn_3_3_gen(bool b)
{
	if(b)
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

void shdn_3_3_clk(bool b)
{
	if(b)
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
	else
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}


void shdn_7_bpog_on()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

void shdn_7_bpog_off()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}

void led_on(unsigned n)
{
	if(n > 6)
		return;
	switch(n){
		case 0:	LO(GPIOB, LED1_bit);break;
		case 1:	LO(GPIOB, LED2_bit);break;
		case 2:	LO(GPIOB, LED3_bit);break;
		case 3:	LO(GPIOB, LED4_bit);break;
		case 4:	HI(GPIOA, LED5_bit);break;
		case 5:	HI(GPIOA, LED6_bit);break;
	}
}

void led_off(unsigned n)
{
	if(n > 6)
		return;
	switch(n){
		case 0:	HI(GPIOB, LED1_bit);break;
		case 1:	HI(GPIOB, LED2_bit);break;
		case 2:	HI(GPIOB, LED3_bit);break;
		case 3:	HI(GPIOB, LED4_bit);break;
		case 4:	LO(GPIOA, LED5_bit);break;
		case 5:	LO(GPIOA, LED6_bit);break;
	}	
}

void led_all_off(void)
{
	HI(GPIOB, LED1_bit);
	HI(GPIOB, LED2_bit);
	HI(GPIOB, LED3_bit);
	HI(GPIOB, LED4_bit);
	LO(GPIOA, LED5_bit);
	LO(GPIOA, LED6_bit);
}

void led_all_on(void)
{
	LO(GPIOB, LED1_bit);
	LO(GPIOB, LED2_bit);
	LO(GPIOB, LED3_bit);
	LO(GPIOB, LED4_bit);
	HI(GPIOA, LED5_bit);
	HI(GPIOA, LED6_bit);	
}

void set_sw_out(bool b)
{
	if(b)
		GPIOA->ODR |= (1<<SW_CONTROL_bit);
	else
		GPIOA->ODR &= ~(1<<SW_CONTROL_bit);
}

void set_adclk_control(bool b)
{
	if(b)
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	
}

void set_ou_pd1(bool b)
{
	if(b)
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	else
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
}

void set_ou_pd2(bool b)
{
	if(b)
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);		
}

void reset(bool b)
{
	if(b)
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);	
}

bool get_achtung()
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == Bit_SET)
		return true;
	else
		return false;
}


/**
* @brief Направление приема/передачи
* @retval true - TX
*/
bool get_usart_dir()
{
	return GPIOC->ODR & (1UL<<DE_RE_bit);
}

void set_usart_tx()
{
	GPIOC->BSRRL |= (1 << 12);
}

void set_usart_rx()
{
	GPIOC->BSRRH |= (1 << 12);
}
