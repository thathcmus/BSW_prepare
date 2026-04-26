#include "can_mcal_bsw.h"
#include "can_app.h"

int main(void) {
    // Register callbacks
    Can_Function_Callback(0, Engine_Handler);
    Can_Function_Callback(2, Brake_Handler);

    uint8_t payload_0[] = {0xFF, 0xAA};
    printf("\n[HARDWARE] CAN interrupt occurred: ID=0 received.\n");
    CAN_Hardware_Interrupt_Handler(0, payload_0, 2);

    uint8_t payload_2[] = {0x77};
    printf("\n[HARDWARE] CAN interrupt occurred: ID=2 received.\n");
    CAN_Hardware_Interrupt_Handler(2, payload_2, 1);

    uint8_t payload_1[] = {0x11, 0x22, 0x33};
    printf("\n[HARDWARE] CAN interrupt occurred: ID=1 received (no subscriber).\n");
    CAN_Hardware_Interrupt_Handler(1, payload_1, 3);

    printf("\n[HARDWARE] CAN interrupt occurred: ID=99 received (noise/error).\n");
    CAN_Hardware_Interrupt_Handler(99, payload_1, 1);

    return 0;
}