/**
* serial.c
* �������� �� ������ � ���������������� ������ �� ���������� RS-485
*
*
*/
#include <stm32f4xx.h> 
#include "stm32f4xx_usart.h"
#include "gpio.h"
#include "irq_prior.h"

/* �������� ������
 */
#define UART_BAUDRATE			115200L

/**
* @brief ���������� USART
*/
// void USART3_IRQHandler (void)
// {
// 	uint8_t c;
// 	
// 	/* ���������� �� ������ ����� */
// 	if ( (USART3->SR & USART_SR_RXNE) ){	
// 		c = (USART3->DR & 0xFF); 
// 		
// 		/* ������������� ���-����� �����, �� � ����� ����������,
//        * ��� ������ �� ������ ���������
//        */
// 		if( !get_usart_dir() ){
// 			MB_Poll(&mb, (uint8_t *)&c, 1 );
// 		}

// 		return;
// 	}
// 	
// 	/* ���������� �� ��������� �������� ������
// 	 */
// 	if ( (USART3->SR & USART_SR_TC)!=RESET ){
// 		set_usart_rx();
// 		USART3->SR &= ~USART_SR_TC;
// 		return;
// 	}
// }

/**
* @breif ������������� USART
*/
void Serial_Init (void) 
{
	USART_InitTypeDef uart;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
//	uart.USART_BaudRate = UART_BAUDRATE;
	uart.USART_WordLength = USART_WordLength_8b;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART3, &uart);
	
	set_usart_rx();
	
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	NVIC_SetPriority(USART3_IRQn, USART_IRQ_PRIOR);
	NVIC_EnableIRQ(USART3_IRQn); 

	/* USART_Init() not configure baudrate valid */
	USART3->BRR = (42000000/UART_BAUDRATE);
	
	USART_Cmd(USART3, ENABLE);
}

/**
* @brief �������� ������ �� RS-485
*/
void Serial_send_bytes(uint8_t* data, int len)
{
	int i;

	set_usart_tx();
	
	for(i = 0; i < len; i++){
		
		while (!(USART3->SR & USART_SR_TXE));
		USART3->DR = data[i];	
		
	}
	
	while (!(USART3->SR & USART_SR_TC));
	
	set_usart_rx();	
}
