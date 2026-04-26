#include <stdio.h>
#include <stdint.h>

// Tạo function ptr gán = NULL
typedef void (*Can_Callback_t)(uint8_t *Data, uint8_t Len);

// Gán Can_Callback_t đến 1 function nào đó mà user sẽ setting có 2 args
void Can_Function_Callback(uint8_t id, Can_Callback_t Can_Callback_Function);

// Handler user funtion that user assgined
void CAN_Hardware_Interrupt_Handler(uint8_t rx_id, uint8_t* rx_data, uint8_t rx_len);
