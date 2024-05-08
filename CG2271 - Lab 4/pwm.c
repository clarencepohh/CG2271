
#include "MKL25Z4.h"
#define CPU_SPEED  48000000
#define PRESCALER  128
#define PTB0_Pin 0
#define PTB1_Pin 1
#define TOTAL_NOTES 7
#define MOD(x) (375000/x)

int notes_freq[] = {262, 294, 330, 349, 392, 440, 494}; // Note C, D, E, F, G, A, B respectively
//130, 146, 164, 174, 196, 220, 246
int get_mod_from_freq(int freq){
	
	double period = 1/(double)freq;
	double time_for_timer_tick = (double)PRESCALER/CPU_SPEED;
	return period/time_for_timer_tick;
	//return (int)((double)(period)* (CPU_SPEED/PRESCALER));
}
/* initPWM() */
void initPWM(void) {
  
  //Enables the clock gate for Port B
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
  
  
  PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3); //We want to enable the Timer/PWM module so we use 3 to select Alternative 3 to enable GPIO, datasheet pg 163
  
  PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK; //Clear bit 10 to 8
  PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3); //We want to enable the Timer/PWM module so we use 3 to select Alternative 3 to enable GPIO, datasheet pg 163
  
  //Enables the clock gate for TPM1 module, datasheet page 208
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; 
  
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK; //Clear bit 25 to 24, datasheet page 195
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Set 01 to bit 25 to 24, MCGFLLCLK clock or MCGPLLCLK/2 is used as clock source for TPM counter clock
  
  TPM1->MOD = 7500; //Set Modulo value = 4 800 000 / 128 = 375 000 / 7500 = 50 Hz
  
  //See datasheet page 553, LPTPM means low power timer/pulse width modulator module
  TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)); //Clears bit 4 to 0, 2 to 0 for PS, 4 to 3 for CMOD
  TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); // LPTPM counter clock mode is selected as 01 (LPTPM counter increments on every LPTPM counter clock), Prescale Factor Selection of 7 is 0b111 which is divide by 128 
  TPM1->SC &= ~(TPM_SC_CPWMS_MASK); //Clears CPWMS (Centre-aligned PWM select). Aka mode = 0 which means LPTPM counter operates in up counting mode.
  
  //See datasheet page 555
  TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); //Clears bit 5 to 2, disabling channel mode 
  TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); // CPWMS = 0, ELSnB:ELSnA = 0b10, MSnB:MSnA = 0b10, this means Mode = Edge-aligned PWM, Config = High-true pulses (clear Output on match, setOutput on reload)
}

/* DELAY FUNCTION */

static void delay (volatile uint32_t nof) {
  volatile uint32_t i = nof*4800;
  while(i!=0) {
    __ASM("NOP");
    i--;
  }
}

static void delay100 (volatile uint32_t nof) {
  for (int i = 0; i < 100; ++i) {
    delay(nof);
  }
}


/* MAIN FUNCTION */

int main(void) { //for part a just comment out the while loop, initPWM(); itself can show the waveform
  
  SystemCoreClockUpdate();
  initPWM();
  
  TPM1_C0V = 0xEA6; //0xEA6 = 3750 (half of 7500) -> 50% duty cycle 
  TPM1_C1V = 0x753; //half of 3750, 1/4 of 7500 -> 25% duty cycle
  
  while(1) {
    for (int i = 0; i < TOTAL_NOTES; i++) {
      TPM1->MOD = get_mod_from_freq(notes_freq[i]);
      TPM1_C0V = TPM1->MOD/2;
      delay(2000);
      
    }
  }
  
}

