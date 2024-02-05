#include "MKL25Z4.h"                    // Device header
#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1
#define MASK(x) (1 << (x))

typedef enum {
	RED,
	BLUE,
	GREEN
} color_t;

unsigned int counter = 0;

void InitGPIO (void)
{
	// Enable Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));
	
	// Configure MUX settings to make all 3 pins GPIO
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers for PortB and PortD
	PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PDDR |= MASK(BLUE_LED);
}

static void delay (volatile uint32_t nof) {
	while(nof!=0) {
		__asm("NOP");
		nof--;
	}
}

static void led_control(color_t color) {
	switch(color){
		case RED:
			PTB->PTOR |= MASK(RED_LED);
			break;
		
		case GREEN:
			PTB->PTOR |= MASK(GREEN_LED);
			break;
		
		case BLUE:
			PTD->PTOR |= MASK(BLUE_LED);
			break;
	}
}

static void flicker(color_t color){
	//turn on LED
	led_control(color);
	delay(0x80000);
	
	//turn off LED
	led_control(color);
}

/* MAIN function */

int main (void) 
{
	InitGPIO();
	PTB->PSOR |= (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PSOR |= MASK(BLUE_LED);
	while(1)
	{
		flicker(RED);
		delay(0x80000);
		flicker(GREEN);
		delay(0x80000);
		flicker(BLUE);
		delay(0x80000);
	}
}
