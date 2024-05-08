#include "macros.h"

void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	//check the status register if the receive data register is full
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		uint8_t data = UART2->D;
		if (data <= 0x80) {
			direction = data;
		} else {
			switch (data){
				case AUDIO_TUNE_1:
					trackPtr = 0;
					notePtr = 0;
					should_pause_music = 0;
					break;
				case AUDIO_TUNE_2:
					trackPtr = 1;
					notePtr = 0;
					should_pause_music = 0;
					break;
				case NO_MUSIC:
					should_pause_music = 1;
					break;
				}
		}
	}
}

void init_UART(void) {
	uint32_t divisor, bus_clock;
	//enable clock gating
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	//pin configuration, alternative 4(page 184), UART form
	PORTE->PCR[UART_RX_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTE->PCR[UART_RX_PIN] |= PORT_PCR_MUX(4);
	//in case we need the transmit functionality
	PORTE->PCR[UART_TX_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTE->PCR[UART_TX_PIN] |= PORT_PCR_MUX(4);	
	//disables receiver and transmitter enable (page 754)
	UART2->C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	//uart bus clock runs at half of the system clock
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	//oversampling rate of 16 times
	divisor = bus_clock / (BAUD_RATE * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	//no need to edit the control 1, status 1 and control 3 registers
	UART2->C1 = 0;
	UART2->C3 = 0;
	//set the irq for uart
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	//enable Rx and interrupts
	UART2->C2 |= ((UART_C2_RE_MASK) | (UART_C2_RIE_MASK));
	
}