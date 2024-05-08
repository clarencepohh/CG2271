#include "macros.h"
#include "led.h"
#include "uart.h"
#include "motors.h"
#include "audio.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"




int main() {
	const osThreadAttr_t thread1_attr ={
	.priority = osPriorityHigh
};
	
	SystemCoreClockUpdate();
	init_UART();
	init_LED();
	turn_off_leds();
	initPWM();
	//PTB->PSOR |= (MASK(RED_LED) | MASK(GREEN_LED));
	//PTD->PSOR |= MASK(BLUE_LED);
	//PTB->PCOR |= MASK(RED_LED);
	
	osKernelInitialize();
	osThreadNew(motor_thread, NULL, NULL);
	osThreadNew(red_led_thread, NULL, NULL);
	osThreadNew(green_led_thread, NULL, NULL);
	osThreadNew(audioThread, NULL, &thread1_attr);
	osKernelStart();
	for(;;){}
	/*
	while(1) {
		//led_toggle(GREEN);
		switch(direction){
			case NORTH:
				led_toggle(RED);
				break;
			case WEST:
				led_toggle(GREEN);
				break;
			case SOUTH:
				led_toggle(BLUE);
				break;
			default:
				turn_off_leds();
		}
	}
	*/
}
