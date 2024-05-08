#include "macros.h"

/* initPWM() */
void initPWM(void) {
  
  //Enables the clock gate for Port B
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
  
  
  
  
  PORTC->PCR[PTC1_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTC->PCR[PTC1_Pin] |= PORT_PCR_MUX(4); //We want to enable the Timer/PWM module so we use 3 to select Alternative 3 to enable GPIO, datasheet pg 163
  
	PORTC->PCR[PTC2_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTC->PCR[PTC2_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC3_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTC->PCR[PTC3_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC4_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTC->PCR[PTC4_Pin] |= PORT_PCR_MUX(4); //We want to enable the Timer/PWM module so we use 3 to select Alternative 3 to enable GPIO, datasheet pg 163
  //Enables the clock gate for TPM1 module, datasheet page 208
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 
  
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK; //Clear bit 25 to 24, datasheet page 195
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Set 01 to bit 25 to 24, MCGFLLCLK clock or MCGPLLCLK/2 is used as clock source for TPM counter clock
  
  TPM0->MOD = 7500; //Set Modulo value = 4 800 000 / 128 = 375 000 / 7500 = 50 Hz
  
  //See datasheet page 553, LPTPM means low power timer/pulse width modulator module
  TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)); //Clears bit 4 to 0, 2 to 0 for PS, 4 to 3 for CMOD
  TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); // LPTPM counter clock mode is selected as 01 (LPTPM counter increments on every LPTPM counter clock), Prescale Factor Selection of 7 is 0b111 which is divide by 128 
  TPM0->SC &= ~(TPM_SC_CPWMS_MASK); //Clears CPWMS (Centre-aligned PWM select). Aka mode = 0 which means LPTPM counter operates in up counting mode.
  
  //See datasheet page 555
  TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); //Clears bit 5 to 2, disabling channel mode 
  TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); // CPWMS = 0, ELSnB:ELSnA = 0b10, MSnB:MSnA = 0b10, this means Mode = Edge-aligned PWM, Config = High-true pulses (clear Output on match, setOutput on reload)

	TPM0_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); //Clears bit 5 to 2, disabling channel mode 
  TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); // CPWMS = 0, ELSnB:ELSnA = 0b10, MSnB:MSnA = 0b10, this means Mode = Edge-aligned PWM,

	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); //Clears bit 5 to 2, disabling channel mode 
  TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); // CPWMS = 0, ELSnB:ELSnA = 0b10, MSnB:MSnA = 0b10, this means Mode = Edge-aligned PWM,

	TPM0_C3SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); //Clears bit 5 to 2, disabling channel mode 
  TPM0_C3SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); // CP
}

	


void motor_thread (void *argument) {
 
  // ...
  for (;;) {
	switch(direction){
		case NORTH: 
						TPM0_C0V = 6000;
						TPM0_C1V = 6000;
						TPM0_C2V = 0;
						TPM0_C3V = 0;
						break;
		case SOUTH: 
						TPM0_C0V = 0;
						TPM0_C1V = 0;
						TPM0_C2V = 6000;
						TPM0_C3V = 6000;
						break;
		case EAST: 
						TPM0_C0V = 6000;
						TPM0_C1V = 0;
						TPM0_C2V = 0;
						TPM0_C3V = 6000;
						break;
		case WEST:
						TPM0_C0V = 0;
						TPM0_C1V = 6000;
						TPM0_C2V = 6000;
						TPM0_C3V = 0;
						break;
		case NORTH_EAST:
						TPM0_C0V = 6000;
						TPM0_C1V = 2500;
						TPM0_C2V = 0;
						TPM0_C3V = 0;
						break;
		case NORTH_WEST:
						TPM0_C0V = 2500;
						TPM0_C1V = 6000;
						TPM0_C2V = 0;
						TPM0_C3V = 0;
						break;
		case SOUTH_EAST:
						TPM0_C0V = 0;
						TPM0_C1V = 0;
						TPM0_C2V = 6000;
						TPM0_C3V = 2500;
						break;
		case SOUTH_WEST:
						TPM0_C0V = 0;
						TPM0_C1V = 0;
						TPM0_C2V = 2500;
						TPM0_C3V = 6000;
						break;
		default:
				TPM0_C0V = 0;
				TPM0_C1V = 0;
				TPM0_C2V = 0;
				TPM0_C3V = 0;
	}
}
}


 