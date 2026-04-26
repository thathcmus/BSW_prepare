#include <stdio.h>
#include <stdint.h>

// Create function pointer assigned to NULL
typedef void (*Can_Callback_t)(uint8_t *Data, uint8_t Len);

// Assign Can_Callback_t to a function that the user will set, having 2 arguments
void Can_Function_Callback(uint8_t id, Can_Callback_t Can_Callback_Function);

// Handler for the user-assigned function
void CAN_Hardware_Interrupt_Handler(uint8_t rx_id, uint8_t* rx_data, uint8_t rx_len);
