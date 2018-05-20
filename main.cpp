// To do: scrap everything, rewrite well

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include "AVRLibrary/CPFECANLib.h"
#include "adc.h"
#include "bms_can.h"

void readtemps(uint16_t*, uint8_t*);

void init();

int main(){

	// Offset each board 250ms from each other to avoid dropping messages
    // _delay_ms(0);

	init();

	uint8_t thermistorCount = 72;

	uint8_t read = 0;

	uint16_t temperatures_16[thermistorCount] = {0};

	uint8_t temperatures_8[thermistorCount*2] = {0};

	// PORTC = 15;

	while(1) {

		if(!read){
			
			readtemps(temperatures_16, temperatures_8);

			read = 1;
		}

		if(TIFR1 & (1<<OCF1A)){

			TIFR1 |= (1<<OCF1A);
			
			send(temperatures_8);
			
			read = 0;

		}

	}


}

void init(){

	//mux setup
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3);		//Set pins C3:C0 to output

	//timer setup
	TCCR1A |= (1<<WGM11) | (1<<WGM10);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS12) | (1<<CS10); 	//1024 prescaler
	OCR1A = 0x3D09; 											//16M/1024

	initADC();
	
	CPFECANLib::init(CPFECANLib::CAN_BAUDRATE::B500K, nullptr);

}


void readtemps(uint16_t* temperatures_16, uint8_t* temperatures_8){

	// ADMUX |= 0x07;
	// PORTC = 2;
	// temperatures_16[0] = highPrecisionRead();

	ADMUX &= 0xE0;
	ADMUX |= 0x03;//change to 03

	for(int i = 0; i < 4; i++){
		PORTC = i;
		temperatures_16[47-i] = highPrecisionRead();
	}
	for(int i = 12; i < 16; i++){
		PORTC = i;
		temperatures_16[27-(i-12)] = highPrecisionRead();
	}


	ADMUX &= 0xE0;
	ADMUX |= 0x04;
	// _delay_ms(10);
	for(int i = 0; i < 8; i++){
		PORTC = i;
		temperatures_16[43-i] = highPrecisionRead();
	}
	for(int i = 8; i < 16; i++){
		PORTC = i;
		temperatures_16[35-(i-8)] = highPrecisionRead();
	}


	ADMUX &= 0xE0;
	ADMUX |= 0x05;

	for(int i = 0; i < 8; i++){
		PORTC = i;
		temperatures_16[55-i] = highPrecisionRead();
	}
	for(int i = 8; i < 16; i++){
		PORTC = i;
		temperatures_16[23-(i-8)] = highPrecisionRead();
	}

	ADMUX &= 0xE0;
	ADMUX |= 0x06;

	for(int i = 0; i < 8; i++){
		PORTC = i;
		temperatures_16[63-i] = highPrecisionRead();
	}
	for(int i = 8; i < 16; i++){
		PORTC = i;
		temperatures_16[15-(i-8)] = highPrecisionRead();
	}


	ADMUX &= 0xE0;
	ADMUX |= 0x07;

	for(int i = 0; i < 8; i++){
		PORTC = i;
		temperatures_16[71-i] = highPrecisionRead();
	}
	for(int i = 8; i < 16; i++){
		PORTC = i;
		temperatures_16[7-(i-8)] = highPrecisionRead();
	}

	for(int i = 0; i < 72; i++){
		temperatures_8[i*2] = (uint8_t)temperatures_16[i];
		temperatures_8[(i*2)+1] = (uint8_t)(temperatures_16[i]>>8);
	}

}

