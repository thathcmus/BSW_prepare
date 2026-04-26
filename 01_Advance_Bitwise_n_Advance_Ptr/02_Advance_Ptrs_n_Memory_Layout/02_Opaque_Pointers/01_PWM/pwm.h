#include <stdio.h>
#include <stdint.h>

typedef struct Pwm_s* PwmHandle_t;

PwmHandle_t PWM_Create(uint32_t frequency);
void PWM_SetDutyCycle(PwmHandle_t handle, uint8_t duty_cycle);
void PWM_Start(PwmHandle_t handle);
void PWM_Stop(PwmHandle_t handle);
void PWM_Destroy(PwmHandle_t handle);