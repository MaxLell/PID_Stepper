#include "main.h"
#include "stepper.h"

void stepper_enable(void)
{
    HAL_GPIO_WritePin(STEPPER_EN_FAULT_GPIO_Port, STEPPER_EN_FAULT_Pin, GPIO_PIN_SET);
}
void stepper_disable(void)
{
    HAL_GPIO_WritePin(STEPPER_EN_FAULT_GPIO_Port, STEPPER_EN_FAULT_Pin, GPIO_PIN_RESET);
}

void stepper_reset()
{
    // stby pin low
    stepper_enter_standby();

    // 100msec delay
    HAL_Delay(100);

    // stby high
    stepper_exit_standby();

    // 100msec delay
    HAL_Delay(100);
}

void stepper_set_direction(uint8_t direction)
{
    HAL_GPIO_WritePin(STEPPER_DIR_MODE4_GPIO_Port, STEPPER_DIR_MODE4_Pin, (direction == CLOCKWISE) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Initialize the GPIOs for the stepper motor
void stepper_init(void)
{
    stepper_disable();
    stepper_set_direction(CLOCKWISE);
    stepper_reset();
}

// Move the motor for a specific number of steps
void stepper_run_x_steps(uint32_t steps)
{
    stepper_exit_standby();
    stepper_enable();

    for (uint32_t i = 0; i < steps; i++)
    {
        HAL_GPIO_WritePin(STEPPER_STCK_MODE3_GPIO_Port, STEPPER_STCK_MODE3_Pin, GPIO_PIN_SET);   // Set STEP pin HIGH
        HAL_Delay(1);                                                                            // Short pulse delay
        HAL_GPIO_WritePin(STEPPER_STCK_MODE3_GPIO_Port, STEPPER_STCK_MODE3_Pin, GPIO_PIN_RESET); // Set STEP pin LOW
        HAL_Delay(1);
    }

    stepper_disable();
    stepper_enter_standby();
}

void stepper_enter_standby(void)
{
    HAL_GPIO_WritePin(STEPPER_STBY_GPIO_Port, STEPPER_STBY_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
}
void stepper_exit_standby(void)
{
    HAL_GPIO_WritePin(STEPPER_STBY_GPIO_Port, STEPPER_STBY_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
}