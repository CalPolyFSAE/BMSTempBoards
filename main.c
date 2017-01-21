//device name for io.h
#define __AVR_AT90CAN128__

//uncomment for 10 bits of precision:
//#define LOW_PRECISION

#include <avr/io.h>
#include "adc.h"


void init();

int main(){
	init();

	uint8_t muxSel = 0;


	while(1) {

		

	}


}

void init(){
	initADC();
}