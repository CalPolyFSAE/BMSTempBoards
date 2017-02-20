#include "bms_can.h"
#include "AVRLibrary/CPFECANLib.h"

unsigned char can_get_mob_free(void);

extern uint32_t ID_BASE;
extern uint8_t BOARD_NUM;

void send(uint8_t *data){
	
	CPFECANLib::MSG msg;

	for(int i = 0; i < 18; i++){

		msg.identifier.extended = ID_BASE + BOARD_NUM + i;
		msg.dlc = 8;
		msg.rtr = 0;
		msg.ide = 1;
		msg.data = data + i*8;

		CPFECANLib::sendMsgUsingMOB(i%15, &msg);
	}

}


//find next free mob- copied out of can_lib.cpp
unsigned char can_get_mob_free(void){

    unsigned char mob_number, page_saved;

    page_saved = CANPAGE;
    for (mob_number = 0; mob_number < NB_MOB; mob_number++)
    {
    	CANPAGE = ((mob_number) << 4);
        if ((CANCDMOB & 0xC0) == 0x00) //! Disable configuration
        {
            CANPAGE = page_saved;
            return (mob_number);
        }
    }
    CANPAGE = page_saved;
    return (NO_MOB);
}
