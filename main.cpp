/*
 * Project: BMS Temp Board
 *
 *  Created on: Dec 18, 2016
 *      Author: nmah
 */

#define OUT4		7
#define OUT3		6
#define OUT0		5
#define OUT2		4
#define OUT1		3

#define AVR_SCK		1

#define S0			3
#define S1			2
#define S2			1
#define S3			0

#define RXCAN		6
#define TXCAN		5

#define TX			1
#define RX			0

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <avr/io.h>

/** pin map on MCU:
 *
 * OUT4 = PF7 Ain for  71-64, 7-0
 * OUT3 = PF6 Ain for 63-56, 15-8
 * OUT0 = PF5 Ain for 55-48, 23-16
 * OUT2 = PF4 Ain for 43-36, 35-28
 * OUT1 = PF3 Ain for 47-44, 27-24
 * AVR_SCK = PB1 SPI Clock
 * S0 = PC3 LSB selector
 * S1 = PC2
 * S2 = PC1
 * S3 = PC0 MSB selector
 * RXCAN[CAN] = PD6 CAN receiving
 * TXCAN[CAN] = PD5 CAN transmitting
 * TX[UART] = PE1 UART TX pin
 * RX[UART] = PE0 UART RX pin
 *
 */

int main(){
	uint8_t x = ADCSRA;
	/** this is an exmple comment
	 * this is just here to how
	 * pushing works in git
	 */
}
