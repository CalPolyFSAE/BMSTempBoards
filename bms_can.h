//minimalistic wrapper for AVR can_lib.h

uint8_t send(st_cmd_t *CANctrl, uint16_t *data, uint8_t size);
