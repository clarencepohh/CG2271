#include "MKL25Z4.h"     
#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1
#define SWITCH_PIN 6 //portD pin 6
#define INTERRUPT_ON_FALLING_EDGE 0b1010
#define MASK(x) (1 << (x))
volatile int current_color = 0;
volatile int flicker_led = 0;

typedef enum {
	RED,
	BLUE,
	GREEN
}color_t;

static void delay(volatile uint32_t nof) {
	while(nof!=0) {
		__asm("NOP");
		nof--;
	}
}
void InitLED(void){
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

void initSwitch(void) {
	//clock for PORTD
	SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//make switch pin gpio
	PORTD->PCR[SWITCH_PIN] |= PORT_PCR_MUX(1);
	//make it a pull up resistor, by enabling pull ups and setting type of 
	PORTD->PCR[SWITCH_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	//set interupt on falling edge
	PORTD->PCR[SWITCH_PIN] |= PORT_PCR_IRQC(INTERRUPT_ON_FALLING_EDGE);
	//set data direction to input 
	PTD->PDDR &= ~MASK(SWITCH_PIN);
	
	//set interrupts
	NVIC_SetPriority(PORTD_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}
void PORTD_IRQHandler() {
	//clear pending irq
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	//update variable TODO
	flicker_led = (flicker_led + 1)%4;
	
	//clear interrupt flag
	PORTD -> ISFR |= MASK(SWITCH_PIN);
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
	}
}

static void flicker(color_t color){
	//turn on LED
		led_control(color);
		delay(0x80000);
		//turn off LED
		led_control(color);
}
static void flicker_in_sequence() {
		flicker(RED);
		delay(0x80000);
		flicker(GREEN);
		delay(0x80000);
		flicker(BLUE);
		delay(0x80000);
}
static void turn_off_leds() {
	PTB->PSOR |= MASK(RED_LED);
	PTB->PSOR |= MASK(GREEN_LED);
	PTD->PSOR |= MASK(BLUE_LED);
}

int main(){
	InitLED();
	initSwitch();
	while(1) {
		switch (flicker_led){
			case 1:
				if(current_color != 1){
					turn_off_leds();
					led_control(RED);
					current_color = 1;
				}
				break;
			case 2:
				if(current_color != 2){
					turn_off_leds();
					led_control(GREEN);
					current_color = 2;
				}
				break;
			case 3:
				if(current_color != 3){
					turn_off_leds();
					led_control(BLUE);
					current_color = 3;
				}
				break;
			case 0 :
				if(current_color != 0){
					turn_off_leds();
					current_color = 0;
				}
				break;
			}
		delay(0x80000);
	}
	
}