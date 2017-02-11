//minimalistic wrapper for AVR can_lib.h
#define ID_BASE 0x00C00000; //base ID for CAN Address
#define BOARD_NUM 1; //represents which board in the modules the current board is
#define NUM_TEMPS 288; //number of temperatures being read per board
#define ID_INDEX BOARD_NUM * NUM_TEMPS; //indexing can message for can boards

uint8_t send(st_cmd_t *CANctrl, uint16_t *data, uint8_t size);
