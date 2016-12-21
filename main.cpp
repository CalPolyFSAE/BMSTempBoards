/*
 * Project: BMS Temp Board
 *
 *  Created on: Dec 18, 2016
 *      Author: Nick Mah, Jason Zhou
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
void Init_ADC3(void){

	ADCSRA = 0x87 ;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x43;    	//Set ADC channel ADC5, set compare voltage to AVcc
}

void Init_ADC4(void){

	ADCSRA = 0x87;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x44;    	//Set ADC channel ADC5, set compare voltage to AVcc
}

void Init_ADC5(void){

	ADCSRA = 0x87;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x45;    	//Set ADC channel ADC5, set compare voltage to AVcc
}

void Init_ADC6(void){

	ADCSRA = 0x87;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x46;    	//Set ADC channel ADC5, set compare voltage to AVcc
}

void Init_ADC7(void){

	ADCSRA = 0x87;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x47;   	//Set ADC channel ADC5, set compare voltage to AVcc
}


int main(){

	// Start Initialize ADCs
	Init_ADC3();
	Init_ADC4();
	Init_ADC5();
	Init_ADC6();
	Init_ADC7();
	// End Initialize ADCs

	//Start Set pin Inputs and Outputs
	DDRC |= (1 << S0) | (1 << S1) | (1 << S2) | (1 << S3);
	//End Set Pin Inputs and Outputs

}
