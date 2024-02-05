#include "MKL25Z4.h"                        // Device header
#define RED_LED                 18          // PortB Pin 18
#define GREEN_LED               19          // PortB Pin 19
#define BLUE_LED                1           // PortD Pin 1
#define SWITCH_PIN              6           // PortD Pin 6
#define MASK(x)                 (1 << (x))
#define FALLING_EDGE_INTERRUPT  1010 

typedef enum {
	RED   = 0,
	GREEN = 1,
	BLUE  = 2
} color_t;

void PORTD_IRQHandler() {
	// Clear pending ISR
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	
	// Update some variable / flag
	
	
	// Clear INT flag
	PORTD->ISFR = 0xffffffff;
}

void initSwitch(void) {
	// enable clock for Port D
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	/* Select GPIO and enable pull-up resistors and interrupts on
	falling edges of pin connected to switch */
	PORTD->PCR[SWITCH_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[SWITCH_PIN] |= PORT_PCR_MUX(1);
	PORTD->PCR[SWITCH_PIN] |= (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
	PORTD->PCR[SWITCH_PIN] |= PORT_PCR_IRQC(FALLING_EDGE_INTERRUPT);
	
	// Set PORT D Switch bit to input
	PTD->PDDR &= ~MASK(SWITCH_PIN);
	
	// Enable Interrupts
	NVIC_SetPriority(PORTD_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}

void initLED(void) { 
	// enable clock for Port D and Port B
	SIM->SCGC5 |= (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTB_MASK);

	// initialize LEDs to be output 
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	
	// Set DDR for ports B and D
	PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PDDR |= MASK(BLUE_LED);
}	

/* MAIN function */
int main() {
	initSwitch();
	initLED();
	
	while(1) {
	
	}
	
}
