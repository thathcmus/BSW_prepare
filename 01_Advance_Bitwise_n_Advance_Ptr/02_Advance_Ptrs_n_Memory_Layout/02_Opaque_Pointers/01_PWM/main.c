#include "pwm.h"

int main() {
    // PWM_Init_Internal();

    PwmHandle_t PWM_Motor = NULL;
    PwmHandle_t PWM_LED = NULL;

    PWM_Motor = PWM_Create(1000);
    PWM_LED = PWM_Create(5000);

    PWM_SetDutyCycle(PWM_Motor, 75);
    PWM_SetDutyCycle(PWM_LED, 50);

    PWM_Start(PWM_Motor);
    PWM_Start(PWM_LED);

    // PWM_Stop(PWM_Motor);
    // PWM_Stop(PWM_LED);  

    PwmHandle_t PWM_Other1 = NULL;
    PwmHandle_t PWM_Other2 = NULL;
    PwmHandle_t PWM_Other3 = NULL;
    PwmHandle_t PWM_Other4 = NULL;

    PWM_Other1 = PWM_Create(10000);
    PWM_Other2 = PWM_Create(20000);
    PWM_Other3 = PWM_Create(20000);
    PWM_Other4 = PWM_Create(20000);
    
    PWM_SetDutyCycle(PWM_Other1, 75);
    PWM_SetDutyCycle(PWM_Other2, 75);
    PWM_SetDutyCycle(PWM_Other3, 75); //PWM ptr is NULL
    PWM_SetDutyCycle(PWM_Other4, 75); //PWM ptr is NULL

    PWM_Destroy(PWM_Other1); //PWM ptr is NULL
    PWM_Destroy(PWM_Other2); //PWM ptr is NULL
    PWM_Destroy(PWM_Other3); //PWM ptr is NULL
    PWM_Destroy(PWM_Other4); //PWM ptr is NULL
    return 0;
}
