
#include "adc.h"
#include <util/delay.h>
void initADC(){

	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //enable, set prescaler to 128

	ADMUX = (1<<REFS0); //preset ADMUX

}


uint16_t highPrecisionRead(){
	ADCSRA |= (1<<ADSC);
	_delay_ms(1);//remove me
	while(ADCSRA & 0x40);
	ADCSRA |= (1<<ADIF);
	uint16_t val = ADC;
	return val;
}
