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
 *Not sure what to do with XTAL1, XTAL2
 *
 * OUT4 = PF7 Ain for  71-64, 7-0
 * OUT3 = PF6 Ain for 63-56, 15-8
 * OUT0 = PF5 Ain for 55-48, 23-16
 * OUT2 = PF4 Ain for 43-36, 35-28
 * OUT1 = PF3 Ain for 47-44, 27-24
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

void Init_ADCs(void){

	ADCSRA = 0x87 ;	//Turn On ADC and set prescaler (CLK/128)
	ADCSRB = 0x00;	//turn off autotrigger
	ADMUX = 0x03;    	//Set ADC channel ADC3, set compare voltage to AVcc
	DIDR0 = (1 << OUT0) | (1 << OUT1) | (1 << OUT2) | (1 << OUT3) | (1 << OUT4);
}

uint8_t Cycle_Through(uint8_t Iterator){ //cycling through mux inputs

	PORTC &= 0xF0; //clearing mux selector
	PORTC |= Iterator; //setting mux selector
	Iterator ++; //iterating selector
	return Iterator;
}

uint16_t read_MCU_ADC(uint8_t OUT){
	uint16_t ADCvoltage;
	ADMUX &= 11111000; //clearing adc mux
	ADMUX |= OUT; //setting mux channel to correct pin
	ADCSRA |= (1 << ADSC); //starting conversion
	while (!(ADCSRA & (1 << ADIF))); //waiting until interrupt flag triggers
	ADCSRA |= (1 << ADSC); //clearing interrupt flag (writing to flag resets flag)
	ADCvoltage = (ADCH << 8) |ADCL; //returning ADC voltage
	return ADCvoltage;
}

int main(){

	// Start Initialize ADCs
	Init_ADCs();
	// End Initialize ADCs

	//Define directions of port pins
	DDRC = (1 << S0) | (1 << S1) | (1 << S2) | (1 << S3);

	uint8_t Iterator = 0; //resetting iterator
	uint8_t OUT = 3; //resetting which mux to output
	while(Iterator < 16){ //cycling through the mux
			read_MCU_ADC(OUT); //reading ADC voltage
			//push_to_MB function (don't know CAN)
			OUT ++;
		if(OUT >= 8){
			Iterator = Cycle_Through(Iterator); //iterating selector
			OUT = 3; //resetting mux output
		}


}

