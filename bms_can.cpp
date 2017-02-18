#include "bms_can.h"
#include "AVRLibrary/CPFECANLib.h"

unsigned char can_get_mob_free(void);

void send(uint8_t *data){
	
	CPFECANLib::MSG msg;

	for(int i = 0; i < 18; i++){

		msg.identifier.extended = ID_BASE + i + ID_INDEX;
		msg.dlc = 8;
		msg.rtr = 0;
		msg.ide = 1;
		msg.data = data + i*8;

		uint8_t MOb = NO_MOB;
		while(MOb == NO_MOB) MOb = can_get_mob_free();

//		if((msg.data[0]) == 0 &&
//				msg.data[1] == 0 &&
//				msg.data[2] == 0 &&
//				msg.data[3] == 0 &&
//				msg.data[4] == 0 &&
//				msg.data[5] == 0 &&
//				msg.data[6] == 0 &&
//				msg.data[7] == 0){
//		} else {
		CPFECANLib::sendMsgUsingMOB(MOb, &msg);
//		}
	}

}


//find next free mob- copied out of can_lib.cpp
unsigned char can_get_mob_free(void){

    unsigned char mob_number, page_saved;

    page_saved = CANPAGE;
    for (mob_number = 0; mob_number < NB_MOB; mob_number++)
    {
        Can_set_mob(mob_number);
        if ((CANCDMOB & 0xC0) == 0x00) //! Disable configuration
        {
            CANPAGE = page_saved;
            return (mob_number);
        }
    }
    CANPAGE = page_saved;
    return (NO_MOB);
}
