#ifndef _ADC_H_
#define _ADC_H_

void initADC();

// uint8_t lowPrecisionRead();			//return value in ADCL
uint16_t highPrecisionRead();		//return value in ADCH and ADCL

void iterateInternal();

#endif