#include "adc.h"

void initADC(){
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //enable, set prescaler to 128

	#ifdef LOW_PRECISION
	ADMUX = (1<<REFS0) | (1<<ADLAR); //use AVcc for ADC voltage reference. implies capacitor on AREF pin; left-adjust ADC for 8 bit precision readings
	#else
	ADMUX = (1<<REFS0);
	#endif
}



uint8_t lowPrecisionRead(){
	ADCSRA |= (1<<ADSC); //adc start conversion
	while(ADCSRA & 0x40) {} //wait for conversion bit to go low
	uint8_t val = ADCH;
	return val;
}

uint16_t highPrecisionRead(){
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & 0x40) {}
	uint16_t val = ((uint16_t)ADCH<<8)|ADCL;
	return val;
}



void iterateInternal(){
	uint8_t cur = ADMUX & 0x0F;
	ADMUX &= 0xF0;
	ADMUX |= cur + 1 ? cur < 7 : 0x03; 
}