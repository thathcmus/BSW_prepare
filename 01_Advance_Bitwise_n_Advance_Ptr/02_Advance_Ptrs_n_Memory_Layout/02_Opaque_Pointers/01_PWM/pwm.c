#include "pwm.h"
#include <stdbool.h>

#define MAX_PWMs 4

struct Pwm_s {
    uint8_t channel_id;
    uint64_t frequency;
    uint8_t duty_cycle;
    bool is_running;
    bool is_allocated;
};

static struct Pwm_s Pwm_Instances[MAX_PWMs];


// static struct Pwm_s* Pwm_FreePool[MAX_PWMs];
// static uint8_t pool_top = MAX_PWMs;

// void PWM_Init_Internal(void) {
//     for (int i = 0; i < MAX_PWMs; i++) {
//         Pwm_FreePool[i] = &Pwm_Instances[i];
//     }
// }

PwmHandle_t PWM_Create(uint32_t frequency){
    for (int i = 0; i < MAX_PWMs; i++) {
        if (Pwm_Instances[i].is_allocated == 0) {
            Pwm_Instances[i].channel_id = i;
            Pwm_Instances[i].frequency = frequency;
            Pwm_Instances[i].duty_cycle = 0;
            Pwm_Instances[i].is_running = false;
            Pwm_Instances[i].is_allocated = 1;
            return &Pwm_Instances[i];
        }
    }
    return NULL;
}

void PWM_SetDutyCycle(PwmHandle_t handle, uint8_t duty_cycle) {
    if (handle == NULL) {
        printf("\n[Error] PWM ptr is NULL.\n");
        return;
    }
    if (duty_cycle > 100) {
        duty_cycle = 100;
    }
    Pwm_Instances[handle->channel_id].duty_cycle = duty_cycle;
    printf("\n[HARDWARE] Write duty_cycle to HW.\n");
}


void PWM_Start(PwmHandle_t handle) {
    if (handle == NULL) {
        printf("\n[Error] PWM ptr is NULL.\n");
        return;
    }

    if (Pwm_Instances[handle->channel_id].is_running == true) {
        printf("\n[Error] PWM is already running, can't start.\n");
        return; 
    }

    Pwm_Instances[handle->channel_id].is_running = true;
    printf("\n[HARDWARE] Start PWM.\n");    
}

void PWM_Stop(PwmHandle_t handle) {
    if (handle == NULL) {
        printf("\n[Error] PWM ptr is NULL.\n");
        return;
    }

    if (Pwm_Instances[handle->channel_id].is_running == false) {
        printf("\n[Error] PWM is already stopping, can't stop.\n");
        return; 
    }

    Pwm_Instances[handle->channel_id].is_running = false;
    printf("\n[HARDWARE] Stop PWM.\n");
}

void PWM_Destroy(PwmHandle_t handle) {
    if (handle == NULL) return;
    
    // Check double
    if (handle->is_allocated == false) {
        return; // Return if destroyed
    }
    
    handle->is_running = false;
    printf("\n[Error] PWM is stopped after call PWM_Destroy.\n");
    handle->is_allocated = false;
    printf("\n[Error] PWM is destroyed.\n");
    // Pwm_FreePool[pool_top++] = handle; // Push lại vào Stack
}