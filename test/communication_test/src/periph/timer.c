/*
 * timer.c
 * Таймер для реализации 
 * точных задержек 
 */
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_tim.h"
#include "timer.h"

#define _APB1_CLK_DIV	8	/* APB1 = 42 MHz */
#define APB1_CLK			42e6
#define PROC_CLK			1000
#define TIM_PRSCKL		100

void timer_init(void)
{
	/* Таймер задержек */
	TIM_TimeBaseInitTypeDef del_tim;	
	
	/* Прерывание системного таймера каждую мс */
	SysTick_Config(SystemCoreClock/1000); 
	
	del_tim.TIM_Prescaler = _APB1_CLK_DIV - 1;
	del_tim.TIM_CounterMode = TIM_CounterMode_Up;
	del_tim.TIM_Period = UINT32_MAX;
	del_tim.TIM_ClockDivision = TIM_CKD_DIV1;
	del_tim.TIM_RepetitionCounter = 0;	/* Not use */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInit(TIM2, &del_tim);
	
	TIM_Cmd(TIM2, ENABLE);
}

/* Функции синхронных задержек */
void delay_s(uint32_t interval)
{
	uint32_t del, tim_curr;
	
	del = interval*10*1000*1000;
	tim_curr = TIM_GetCounter(TIM2);
	
	while((TIM_GetCounter(TIM2) - tim_curr) < del)
	{
	}
}

void delay_ms(uint32_t interval)
{
	uint32_t del, tim_curr;
	
	del = interval*10*1000;
	tim_curr = TIM_GetCounter(TIM2);
	
	while((TIM_GetCounter(TIM2) - tim_curr) < del)
	{
	}
}

void delay_us(uint32_t interval)
{
	uint32_t del, tim_curr;
	
	del = interval*10;
	tim_curr = TIM_GetCounter(TIM2);
	
	while((TIM_GetCounter(TIM2) - tim_curr) < del)
	{
	}	
}

/* Функции работы с асинхронными таймерами */
uint32_t tim_curr[TIMERS_NUM];
uint32_t del[TIMERS_NUM];

void timer_100ns_set(int tm, uint32_t interval)
{
	del[tm] = interval;
	tim_curr[tm] = TIM_GetCounter(TIM2);
}

void timer_us_set(int tm, uint32_t interval)
{
	del[tm] = interval*10;
	tim_curr[tm] = TIM_GetCounter(TIM2);	
}

void timer_ms_set(int tm, uint32_t interval)
{
	del[tm] = interval*10*1000;
	tim_curr[tm] = TIM_GetCounter(TIM2);
}

bool timer_complete(int tm)
{
	if((TIM_GetCounter(TIM2) - tim_curr[tm]) < del[tm])
		return false;
	else 
		return true;
}

/* Обработка прерывания системного таймера */
static volatile uint32_t msTicks;
void SysTick_Handler(void)
{
  msTicks++;
}
