#include "can_mcal_bsw.h"
#include "can_app.h"

int main() {
    // Register function
    Can_Function_Callback(0, Engine_Handler);
    Can_Function_Callback(2, Brake_Handler);

    uint8_t payload_0[] = {0xFF, 0xAA};
    printf("\n[HARDWARE] Ngat CAN xay ra: ID=0 bay vao.\n");
    CAN_Hardware_Interrupt_Handler(0, payload_0, 2);

    // Giả lập 2: Phần cứng nhận bản tin ID = 2 (Gửi cho Phanh)
    uint8_t payload_2[] = {0x77};
    printf("\n[HARDWARE] Ngat CAN xay ra: ID=2 bay vao.\n");
    CAN_Hardware_Interrupt_Handler(2, payload_2, 1);

    // Giả lập 3: Phần cứng nhận bản tin ID = 1 (CHƯA AI ĐĂNG KÝ)
    uint8_t payload_1[] = {0x11, 0x22, 0x33};
    printf("\n[HARDWARE] Ngat CAN xay ra: ID=1 bay vao.\n");
    CAN_Hardware_Interrupt_Handler(1, payload_1, 3); // Code an toàn sẽ không bị Crash

    // Giả lập 4: Lỗi nhiễu phần cứng, ID = 99
    printf("\n[HARDWARE] Ngat CAN xay ra: ID=99 (Loi nhieu).\n");
    CAN_Hardware_Interrupt_Handler(99, payload_1, 1); // Code an toàn sẽ chặn lại
    return 0;
}
