#include "bms_can.h"

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