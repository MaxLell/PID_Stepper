#ifndef STEPPER_H
#define STEPPER_H

#include "stdint.h"

#define STEPS_PER_REV 200 // Number of steps per revolution (e.g., 1.8° per step = 200 steps per revolution)

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

void stepper_init(void);
void stepper_enable(void);
void stepper_disable(void);
void stepper_reset(void);
void stepper_set_direction(uint8_t direction);
void stepper_run_x_steps(uint32_t x);

void stepper_enter_standby(void);
void stepper_exit_standby(void);

#endif // STEPPER_H
