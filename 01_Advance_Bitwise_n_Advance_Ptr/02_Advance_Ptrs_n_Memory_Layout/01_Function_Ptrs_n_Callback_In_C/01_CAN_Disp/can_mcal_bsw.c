#include "can_mcal_bsw.h"

#define MAX_ID 5

static Can_Callback_t Can_Callback_Table[MAX_ID] = {NULL, NULL, NULL, NULL, NULL};

void Can_Function_Callback(uint8_t id, Can_Callback_t Can_Callback_Function) {
    if(id < MAX_ID) {
        Can_Callback_Table[id] = Can_Callback_Function;
    }
    else {
        printf("[Error] Invalid ID.\n"); fflush(stdout);
        return;
    }
}

void CAN_Hardware_Interrupt_Handler(uint8_t rx_id, uint8_t* rx_data, uint8_t rx_len)
{
    if((rx_id < MAX_ID) && (Can_Callback_Table[rx_id] != NULL)) {
        printf("[Info] Receive from ID %d.\n", rx_id); fflush(stdout);
        Can_Callback_Table[rx_id](rx_data, rx_len);
    }
    else {
        printf("[Error] Function ptr is NULL.\n"); fflush(stdout);
        return;
    }
}
