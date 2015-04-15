/**
***************************************************
* @breif Тест ModBus библиотеки
* @autor
* @date
***************************************************
*/
#include <stdbool.h>
#include "gpio.h"
#include "timer.h"
#include "serial.h"

int main()
{
	timer_init();
	gpio_init();
	
	while(true){
		led_on(0);
		delay_ms(1000);
		led_off(0);
		delay_ms(1000);
	}
}
