#pragma once
#include "MKL25Z4.h"

#define MASK(x)       (1 << (x))
#define SYSCLK 48000000

#define UART_IRQ_PRIO 2
#define UART_TX_PIN 22
#define UART_RX_PIN 23
#define BAUD_RATE 9600
#define PTC1_Pin 1
#define PTC2_Pin 2
#define PTC3_Pin 3
#define PTC4_Pin 4

#define NORTH 0x10
#define WEST 0x20
#define EAST 0x30
#define SOUTH 0x40
#define NORTH_WEST 0x50
#define NORTH_EAST 0x60
#define SOUTH_WEST 0x70
#define SOUTH_EAST 0x80

volatile uint8_t direction = 0;

#define RED_LED_PORTS [8] = {PORTD, PORTD, PORTD, PORTD, PORTD, PORTD, PORTC, PORTC}
#define RED_LED_PINA 13  
#define RED_LED_GPIO [8] = {PTD, PTD, PTD, PTD, PTD, PTD, PTC, PTC}
uint8_t GREEN_LED_PINS [8] = {5,0,2,3,12,13,16,17};
GPIO_Type* GREEN_LED_GPIO [8] = {PTD, PTD, PTD, PTD, PTC, PTC, PTC, PTC};
PORT_Type* GREEN_LED_PORTS [8] = {PORTD, PORTD, PORTD, PORTD, PORTC, PORTC, PORTC, PORTC};
//led testing
#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1

// Audio
#define AUDIO_TUNE_1 0x90
#define AUDIO_TUNE_2 0xA0
#define NO_MUSIC 0xB0

#define AUDIO_PRESCALAR      64 // x2 because center-aligned
#define AUDIO_PIN            0  // Port B Pin 0
#define AUDIO_VOLUME_DIVIDER (100 * 10)

#define NOTE_REST 65535

#define NOTE_C3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 130.81)
#define NOTE_CS3  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 138.59)
#define NOTE_D3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 146.83)
#define NOTE_DS3  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 155.56)
#define NOTE_E3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 164.81)
#define NOTE_F3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 174.61)
#define NOTE_FS3  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 185)
#define NOTE_G3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 196)
#define NOTE_GS3  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 207.65)
#define NOTE_A3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 220)
#define NOTE_AS3  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 233.08)
#define NOTE_B3   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 246.94)

#define NOTE_C4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 261.63)
#define NOTE_CS4  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 277.18)
#define NOTE_D4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 293.66)
#define NOTE_DS4  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 311.13)
#define NOTE_E4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 329.63)
#define NOTE_F4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 349.23)
#define NOTE_FS4  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 369.99)
#define NOTE_G4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 392)
#define NOTE_GS4  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 415.3)
#define NOTE_A4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 440)
#define NOTE_AS4  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 466.16)
#define NOTE_B4   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 493.88)

#define NOTE_C5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 523.25)
#define NOTE_CS5  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 554.37)
#define NOTE_D5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 587.33)
#define NOTE_DS5  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 622.25)
#define NOTE_E5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 659.25)
#define NOTE_F5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 698.46)
#define NOTE_FS5  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 739.99)
#define NOTE_G5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 783.99)
#define NOTE_GS5  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 830.61)
#define NOTE_A5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 880)
#define NOTE_AS5  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 932.33)
#define NOTE_B5   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 987.77)

#define NOTE_C6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1046.5)
#define NOTE_CS6  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1108.73)
#define NOTE_D6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1174.66)
#define NOTE_DS6  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1244.51)
#define NOTE_E6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1318.51)
#define NOTE_F6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1396.91)
#define NOTE_FS6  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1479.98)
#define NOTE_G6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1567.98)
#define NOTE_GS6  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1661.22)
#define NOTE_A6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1760)
#define NOTE_AS6  (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1864.66)
#define NOTE_B6   (uint16_t) (SYSCLK / AUDIO_PRESCALAR / 1975.53)

#define breve 1000
#define dot_croct 750
#define crotchet 500
#define dot_quav 375
#define quaver 250
#define semi_quav 125

const uint16_t NOTE_VALUES_2[] = {NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D5, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_REST};
const uint16_t NOTE_DELAYS_2[] = {semi_quav,semi_quav,semi_quav,semi_quav,dot_quav,dot_quav,dot_croct,semi_quav,semi_quav,semi_quav,semi_quav,dot_quav,dot_quav,dot_quav,semi_quav,quaver,semi_quav,semi_quav,semi_quav,semi_quav,crotchet,quaver,dot_quav,semi_quav,quaver,quaver,quaver,crotchet,breve,semi_quav,semi_quav,semi_quav,semi_quav,dot_quav,dot_quav,dot_croct,semi_quav,semi_quav,semi_quav,semi_quav,crotchet,quaver,dot_quav, semi_quav, quaver, semi_quav,semi_quav,semi_quav,semi_quav,crotchet,quaver,dot_quav, semi_quav, crotchet,quaver,crotchet,breve,semi_quav};

#define BREVE 920
#define DOT_CROCHT 675
#define CROTCHET 460
#define DOT_QUAV 345
#define QUAVER 230
#define DOT_SEMIQUAV 173
#define SEMI_QUAV 115
	
const uint16_t NOTE_VALUES_1[] = {NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4,  NOTE_F4,  NOTE_D4, NOTE_F4, NOTE_G4, NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, NOTE_GS4,  NOTE_G4,  NOTE_F4,  NOTE_D4, NOTE_F4, NOTE_G4};
const uint16_t NOTE_DELAYS_1[] = {SEMI_QUAV, SEMI_QUAV, QUAVER, DOT_QUAV, QUAVER, QUAVER, QUAVER, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, QUAVER, DOT_QUAV, QUAVER, QUAVER, QUAVER, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, QUAVER, DOT_QUAV, QUAVER, QUAVER, QUAVER, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV, QUAVER, DOT_QUAV, QUAVER, QUAVER, QUAVER, SEMI_QUAV, SEMI_QUAV, SEMI_QUAV};

const uint8_t ADSR_VALUES[] = {0, 50, 75, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, 0, 0};
const uint16_t* NOTE_VALUES[] = {NOTE_VALUES_1, NOTE_VALUES_2};
const uint16_t* NOTE_DELAYS[] = {NOTE_DELAYS_1, NOTE_DELAYS_2};
const uint32_t NOTE_SIZES[] = {sizeof(NOTE_VALUES_1) / sizeof(NOTE_VALUES_1[0]), sizeof(NOTE_VALUES_2) / sizeof(NOTE_VALUES_2[0])};

volatile uint16_t trackPtr = 0, notePtr = 0, should_pause_music = 0;
