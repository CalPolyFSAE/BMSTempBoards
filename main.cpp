//device name for io.h	
#define __AVR_AT90CAN128__

#define ID_BASE 0x00C00000; //base ID for CAN Address
#define BOARD_NUM 0x0; //represents which board in the modules the current board is
#define NUM_TEMPS 288; //number of temperatures being read per board

//uncomment for only 8 bits of precision:
//#define LOW_PRECISION

#include <avr/io.h>
#include <CPFECANLib.h>
#include "adc.h"
#include "bms_can.h"

void init();

int main(){

	init();

	uint8_t thermistorCount = 72;

	uint8_t read = 0;

	uint16_t temperatures_16[thermistorCount];

	uint8_t temperatures_8[thermistorCount*2];

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


	
}




void readtemps(uint16_t* temperatures_16, uint8_t* temperatures_8){
	PORTC = 0x00;

	temperatures[55] = highPrecisionRead();
	temperatures[47] = highPrecisionRead();
	temperatures[43] = highPrecisionRead();
	temperatures[63] = highPrecisionRead();
	temperatures[71] = highPrecisionRead();

	PORTC = 0x01;

	temperatures[54] = highPrecisionRead();
	temperatures[46] = highPrecisionRead();
	temperatures[42] = highPrecisionRead();
	temperatures[62] = highPrecisionRead();
	temperatures[70] = highPrecisionRead();

	PORTC = 0x02;

	temperatures[53] = highPrecisionRead();
	temperatures[45] = highPrecisionRead();
	temperatures[41] = highPrecisionRead();
	temperatures[61] = highPrecisionRead();
	temperatures[69] = highPrecisionRead();

	PORTC = 0x03;

	temperatures[52] = highPrecisionRead();
	temperatures[44] = highPrecisionRead();
	temperatures[40] = highPrecisionRead();
	temperatures[60] = highPrecisionRead();
	temperatures[68] = highPrecisionRead();

	PORTC = 0x04;

	temperatures[51] = highPrecisionRead();
	iterateInternal();
	temperatures[39] = highPrecisionRead();
	temperatures[59] = highPrecisionRead();
	temperatures[67] = highPrecisionRead();

	PORTC = 0x05;

	temperatures[50] = highPrecisionRead();
	iterateInternal();
	temperatures[38] = highPrecisionRead();
	temperatures[58] = highPrecisionRead();
	temperatures[66] = highPrecisionRead();

	PORTC = 0x06;

	temperatures[49] = highPrecisionRead();
	iterateInternal();
	temperatures[37] = highPrecisionRead();
	temperatures[57] = highPrecisionRead();
	temperatures[65] = highPrecisionRead();

	PORTC = 0x07;

	temperatures[48] = highPrecisionRead();
	iterateInternal();
	temperatures[36] = highPrecisionRead();
	temperatures[56] = highPrecisionRead();
	temperatures[64] = highPrecisionRead();

	PORTC = 0x08;

	temperatures[23] = highPrecisionRead();
	iterateInternal();
	temperatures[35] = highPrecisionRead();
	temperatures[15] = highPrecisionRead();
	temperatures[7] = highPrecisionRead();

	PORTC = 0x09;

	temperatures[22] = highPrecisionRead();
	iterateInternal();
	temperatures[34] = highPrecisionRead();
	temperatures[14] = highPrecisionRead();
	temperatures[6] = highPrecisionRead();

	PORTC = 0x0A;

	temperatures[21] = highPrecisionRead();
	iterateInternal();
	temperatures[33] = highPrecisionRead();
	temperatures[13] = highPrecisionRead();
	temperatures[5] = highPrecisionRead();

	PORTC = 0x0B;

	temperatures[20] = highPrecisionRead();
	iterateInternal();
	temperatures[32] = highPrecisionRead();
	temperatures[12] = highPrecisionRead();
	temperatures[4] = highPrecisionRead();

	PORTC = 0x0C;

	temperatures[19] = highPrecisionRead();
	temperatures[27] = highPrecisionRead();
	temperatures[31] = highPrecisionRead();
	temperatures[11] = highPrecisionRead();
	temperatures[3] = highPrecisionRead();

	PORTC = 0x0D;

	temperatures[18] = highPrecisionRead();
	temperatures[26] = highPrecisionRead();
	temperatures[30] = highPrecisionRead();
	temperatures[10] = highPrecisionRead();
	temperatures[2] = highPrecisionRead();

	PORTC = 0x0E;

	temperatures[17] = highPrecisionRead();
	temperatures[25] = highPrecisionRead();
	temperatures[29] = highPrecisionRead();
	temperatures[9] = highPrecisionRead();
	temperatures[1] = highPrecisionRead();

	PORTC = 0x0F;

	temperatures[16] = highPrecisionRead();
	temperatures[24] = highPrecisionRead();
	temperatures[28] = highPrecisionRead();
	temperatures[8] = highPrecisionRead();
	temperatures[0] = highPrecisionRead();

	for(int i = 0; i < 72; i++){
		temperatures_8[2*i] = (uint8_t)(temperatures_16[i]>>8);
		temperatures_8[2*i+1] = (uint8_t)(temperatures_16[i]);
	}

}
