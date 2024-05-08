#pragma once
#include "MKL25Z4.h"

#define MASK(x)       (1 << (x))
#define SYSCLK 48000000

#define UART_IRQ_PRIO 2
#define UART_TX_PIN 22
#define UART_RX_PIN 23
#define BAUD_RATE 9600

#define NORTH 0x10
#define WEST 0x20
#define EAST 0x30
#define SOUTH 0x40
#define NORTH_WEST 0x50
#define NORTH_EAST 0x60
#define SOUTH_WEST 0x70
#define SOUTH_EAST 0x80
volatile uint8_t direction = 0;


//led testing
#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1
