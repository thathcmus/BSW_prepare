#include "can_app.h"

void Engine_Handler(uint8_t* rx_data, uint8_t rx_len) {
    printf("\t[APP]Engine_Handler\n"); fflush(stdout);
    printf("\t\t[APP]Len = %d byte(s)\n", rx_len); fflush(stdout);
    printf("\t\t[APP]Data[0] = 0x%x\n", rx_data[0]); fflush(stdout);
}

void Brake_Handler(uint8_t* rx_data, uint8_t rx_len) {
    printf("\t[APP]Brake_Handler\n"); fflush(stdout);
    printf("\t\t[APP]Len = %d byte(s)\n", rx_len); fflush(stdout);
    printf("\t\t[APP]Data[0] = 0x%x\n", rx_data[0]); fflush(stdout);
}