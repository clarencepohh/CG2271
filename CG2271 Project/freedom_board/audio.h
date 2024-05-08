#include "macros.h"
#include "cmsis_os2.h"
#include "RTE_Components.h"             // Component selection
#include CMSIS_device_header
#include "MKL25Z4.h" 

void initAudioPWM(void) {
    // Provide power to clock for Port B GPIO and TPM1
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
    // Set functionality of Port B Pin 0 to TPM1 channel 0 
	PORTB->PCR[AUDIO_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[AUDIO_PIN] |= PORT_PCR_MUX(3);
	
    // Select clock source for TPM
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
    // Set PWM pulse to high-true
	TPM1_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM1_C0SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);
	
    // Set TPM1 as center-aligned, TPM1 prescalar as 32, start TPM1
	TPM1->SC |= TPM_SC_CPWMS_MASK;
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(5));
}

void audioThread(void* argument) {
    uint8_t adsrPtr = 0;
    initAudioPWM();
    
    while (1) {
        if (should_pause_music) {
            TPM1_C0V = 0;
            osDelay(500);
            continue;
        }
        // Update frequency/period
        TPM1->MOD = NOTE_VALUES[trackPtr][notePtr];
			  TPM1_C0V = TPM1->MOD != NOTE_REST ? (TPM1->MOD * (uint32_t) ADSR_VALUES[adsrPtr] / AUDIO_VOLUME_DIVIDER) : 0;
        
        // Wait for and handle next note
        osDelay(NOTE_DELAYS[trackPtr][notePtr] / 16);
        if (++adsrPtr == 16) {
            adsrPtr = 0;
            notePtr = notePtr == NOTE_SIZES[trackPtr] - 1 ? 0 : notePtr + 1;
        }
    }
}
