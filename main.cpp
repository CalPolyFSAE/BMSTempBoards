//device name for io.h
#define __AVR_AT90CAN128__

//uncomment for 10 bits of precision:
//#define LOW_PRECISION

#include <avr/io.h>
#include <arduino/canlib.h>
#include "adc.h"

extern canlib CAN;

void init();

int main(){

	init();

	st_cmd_t CANctrl;

	uint8_t muxSel = 0;

	uint16_t temp[72];


	while(1) {

		

	}


}

void init(){

	initADC();

	CAN.init(0);
	
}


uint8_t send(st_cmd_t *CANctrl, uint16_t *data, uint8_t size){
	
	CANctrl->cmd = CMD_TX_DATA;

	for(uint8_t i = 0; i < size, i+=8){
		CANctrl->dlc = 8;
		CANctrl->pt_data = data + i;
		if(CAN.cmd(CANctrl) == CAN_CMD_REFUSED) return 0;
	}

	if(size%8 == 0) return 1;

	CANctrl->dlc = size % 8;
	CANctrl->pt_data = data + size - (size % 8)
	if(CAN.cmd(CANctrl) == CAN_CMD_REFUSED) return 0;

	return 1;

}