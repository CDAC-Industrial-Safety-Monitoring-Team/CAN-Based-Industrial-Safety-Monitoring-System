/*
 * buzzer.c
 *
 *  Created on:
 *      Author: Moeen Sheikh
 */

#include "buzzer.h"

#define BUZZER_PORT    GPIOB
#define BUZZER_PIN     GPIO_PIN_4

void Buzzer_Update(SystemStatus_t Status)
{
    static uint32_t PreviousTick = 0;
    static GPIO_PinState BuzzerState = GPIO_PIN_RESET;

    if (Status == STATUS_NORMAL)
    {
        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
        BuzzerState = GPIO_PIN_RESET;
        PreviousTick = HAL_GetTick();
        return;
    }

    if ((HAL_GetTick() - PreviousTick) >= 200)
    {
        PreviousTick = HAL_GetTick();

        if (BuzzerState == GPIO_PIN_RESET)
        {
            BuzzerState = GPIO_PIN_SET;
        }
        else
        {
            BuzzerState = GPIO_PIN_RESET;
        }

        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, BuzzerState);
    }
}
