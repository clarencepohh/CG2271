#include "macros.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

typedef enum {
	RED,
	BLUE,
	GREEN
}color_t;

static void led_toggle(color_t color) {
	switch(color){
		case RED:
			PTB->PTOR |= MASK(RED_LED);
			break;
		case GREEN:
			PTB->PTOR |= MASK(GREEN_LED);
			break;
		case BLUE:
			PTD->PTOR |= MASK(BLUE_LED);
	}
}

static void turn_off_leds() {
	PTB->PSOR |= MASK(RED_LED);
	PTB->PSOR |= MASK(GREEN_LED);
	PTD->PSOR |= MASK(BLUE_LED);
}

void red_led_thread (void *argument){
	for(;;){ 
		/*
		PTD->PTOR |= MASK(RED_LED_PIND);
		osDelay(1000);
		PTD->PTOR |= MASK(RED_LED_PIND);
		osDelay(1000);
		*/
		if(!direction){
			PTA->PSOR |= MASK(RED_LED_PINA);
			osDelay(250);
			PTA->PCOR |= MASK(RED_LED_PINA);
			osDelay(250);
		}
		else{
			PTA->PSOR |= MASK(RED_LED_PINA);
			osDelay(500);
			PTA->PCOR |= MASK(RED_LED_PINA);
			osDelay(500);
		}
	}
}

void green_led_thread (void *argument){
	for(;;){
		if(!direction){
			for(int i =0; i<8; i++){
				GREEN_LED_GPIO[i]->PSOR |= MASK(GREEN_LED_PINS[i]);
				
			}
		}
		else{
			for(int j =0; j<8; j++){
				GREEN_LED_GPIO[j]->PCOR |= MASK(GREEN_LED_PINS[j]);
			}
			for(int i =0; i<8; i++){
				if(!direction){break;};
				GREEN_LED_GPIO[i]->PSOR |= MASK(GREEN_LED_PINS[i]);
				osDelay(500);
				GREEN_LED_GPIO[i]->PCOR |= MASK(GREEN_LED_PINS[i]);
					
			}
		}
	}
}


void init_LED(void){
	// Enable Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTC_MASK) | (SIM_SCGC5_PORTD_MASK) | (SIM_SCGC5_PORTA_MASK));
	// Configure MUX settings for red led pins
	PORTA->PCR[RED_LED_PINA] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[RED_LED_PINA] |= PORT_PCR_MUX(1);
	// Configure MUX settings and set Data Direction Registers for green led pins
	for(int i =0; i<8; i++){
		GREEN_LED_PORTS[i]->PCR[GREEN_LED_PINS[i]] &= ~PORT_PCR_MUX_MASK;
		GREEN_LED_PORTS[i]->PCR[GREEN_LED_PINS[i]] |= PORT_PCR_MUX(1);
		GREEN_LED_GPIO[i]->PDDR |= MASK(GREEN_LED_PINS[i]);
	}
	// Set Data Direction Registers for red led pins
	PTA->PDDR |= MASK(RED_LED_PINA);
	
}

		
