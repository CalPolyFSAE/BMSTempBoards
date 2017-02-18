//device name for io.h	
#define __AVR_AT90CAN128__

#define ID_BASE 0x00C00000; //base ID for CAN Address
#define BOARD_NUM 0x0; //represents which board in the modules the current board is
#define NUM_TEMPS 288; //number of temperatures being read per board

//uncomment for only 8 bits of precision:
//#define LOW_PRECISION

#include <avr/io.h>
#include <AVRLibrary/CPFECANLib.h>
#include "adc.h"
#include "bms_can.h"

CPFECANLib can;

uint16_t highPrecisionRead(){
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & 0x40);
	uint16_t val = ADC;
	iterateInternal();
	return val;
}

void iterateInternal(){
	uint8_t cur = ADMUX & 0x0F;
	ADMUX &= 0xF0;
	ADMUX |= cur + 1 ? cur < 7 : 0x03;
}

void initADC(){
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //enable, set prescaler to 128

	//ADMUX = (1<<REFS0) | (1<<ADLAR); //use AVcc for ADC voltage reference. implies capacitor on AREF pin; left-adjust ADC for 8 bit precision readings
	ADMUX = (1<<REFS0) | 0x03; //preset ADMUX
}


void readtemps(uint16_t*, uint8_t*);

void init();

int main(){

	init();

	uint8_t thermistorCount = 72;

	uint8_t read = 0;

	uint16_t temperatures_16[thermistorCount];

	uint8_t temperatures_8[thermistorCount*2];

	uint8_t dummy[thermistorCount*2] = {0};

	while(1) {

		if(!read){
			
			readtemps(temperatures_16, temperatures_8);

			read = 1;
		}

		if(TIFR1 & (1<<OCF1A)){

			TIFR1 |= (1<<OCF1A);
			
			send(temperatures_8);
			
			//TCNT1 = 0x0; //reset clock

			read = 0;

		}		

	}


}

void init(){

	//mux setup
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3);

	//timer setup
	TCCR1A |= (1<<WGM11) | (1<<WGM10);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS12) | (1<<CS10); 	//1024 prescaler
	OCR1A = 0x3D09; 											// 16M/1024

	initADC();
	


	CPFECANLib::init(CPFECANLib::CAN_BAUDRATE::B1M, nullptr);

}




void readtemps(uint16_t* temperatures_16, uint8_t* temperatures_8){
	PORTC = 0x00;

	temperatures_16[55] = highPrecisionRead();
	temperatures_16[47] = highPrecisionRead();
	temperatures_16[43] = highPrecisionRead();
	temperatures_16[63] = highPrecisionRead();
	temperatures_16[71] = highPrecisionRead();

	PORTC = 0x01;

	temperatures_16[54] = highPrecisionRead();
	temperatures_16[46] = highPrecisionRead();
	temperatures_16[42] = highPrecisionRead();
	temperatures_16[62] = highPrecisionRead();
	temperatures_16[70] = highPrecisionRead();

	PORTC = 0x02;

	temperatures_16[53] = highPrecisionRead();
	temperatures_16[45] = highPrecisionRead();
	temperatures_16[41] = highPrecisionRead();
	temperatures_16[61] = highPrecisionRead();
	temperatures_16[69] = highPrecisionRead();

	PORTC = 0x03;

	temperatures_16[52] = highPrecisionRead();
	temperatures_16[44] = highPrecisionRead();
	temperatures_16[40] = highPrecisionRead();
	temperatures_16[60] = highPrecisionRead();
	temperatures_16[68] = highPrecisionRead();

	PORTC = 0x04;

	temperatures_16[51] = highPrecisionRead();
	iterateInternal();
	temperatures_16[39] = highPrecisionRead();
	temperatures_16[59] = highPrecisionRead();
	temperatures_16[67] = highPrecisionRead();

	PORTC = 0x05;

	temperatures_16[50] = highPrecisionRead();
	iterateInternal();
	temperatures_16[38] = highPrecisionRead();
	temperatures_16[58] = highPrecisionRead();
	temperatures_16[66] = highPrecisionRead();

	PORTC = 0x06;

	temperatures_16[49] = highPrecisionRead();
	iterateInternal();
	temperatures_16[37] = highPrecisionRead();
	temperatures_16[57] = highPrecisionRead();
	temperatures_16[65] = highPrecisionRead();

	PORTC = 0x07;

	temperatures_16[48] = highPrecisionRead();
	iterateInternal();
	temperatures_16[36] = highPrecisionRead();
	temperatures_16[56] = highPrecisionRead();
	temperatures_16[64] = highPrecisionRead();

	PORTC = 0x08;

	temperatures_16[23] = highPrecisionRead();
	iterateInternal();
	temperatures_16[35] = highPrecisionRead();
	temperatures_16[15] = highPrecisionRead();
	temperatures_16[7] = highPrecisionRead();

	PORTC = 0x09;

	temperatures_16[22] = highPrecisionRead();
	iterateInternal();
	temperatures_16[34] = highPrecisionRead();
	temperatures_16[14] = highPrecisionRead();
	temperatures_16[6] = highPrecisionRead();

	PORTC = 0x0A;

	temperatures_16[21] = highPrecisionRead();
	iterateInternal();
	temperatures_16[33] = highPrecisionRead();
	temperatures_16[13] = highPrecisionRead();
	temperatures_16[5] = highPrecisionRead();

	PORTC = 0x0B;

	temperatures_16[20] = highPrecisionRead();
	iterateInternal();
	temperatures_16[32] = highPrecisionRead();
	temperatures_16[12] = highPrecisionRead();
	temperatures_16[4] = highPrecisionRead();

	PORTC = 0x0C;

	temperatures_16[19] = highPrecisionRead();
	temperatures_16[27] = highPrecisionRead();
	temperatures_16[31] = highPrecisionRead();
	temperatures_16[11] = highPrecisionRead();
	temperatures_16[3] = highPrecisionRead();

	PORTC = 0x0D;

	temperatures_16[18] = highPrecisionRead();
	temperatures_16[26] = highPrecisionRead();
	temperatures_16[30] = highPrecisionRead();
	temperatures_16[10] = highPrecisionRead();
	temperatures_16[2] = highPrecisionRead();

	PORTC = 0x0E;

	temperatures_16[17] = highPrecisionRead();
	temperatures_16[25] = highPrecisionRead();
	temperatures_16[29] = highPrecisionRead();
	temperatures_16[9] = highPrecisionRead();
	temperatures_16[1] = highPrecisionRead();

	PORTC = 0x0F;

	temperatures_16[16] = highPrecisionRead();
	temperatures_16[24] = highPrecisionRead();
	temperatures_16[28] = highPrecisionRead();
	temperatures_16[8] = highPrecisionRead();
	temperatures_16[0] = highPrecisionRead();

	for(int i = 0; i < 72; i++){
		temperatures_8[2*i] = (uint8_t)(temperatures_16[i]>>8);
		temperatures_8[2*i+1] = (uint8_t)(temperatures_16[i]);
	}

}
