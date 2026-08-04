/*
 * indicator.c
 *
 *  Created on: 19-Jul-2026
 *      Author: Aditi Nagane 
 */

#include "indicator.h"

void Indicator_Update(SystemStatus_t Status)
{
    if(Status == STATUS_NORMAL)
    {
        /* Green LED ON */
        HAL_GPIO_WritePin(GREEN_LED_PORT,
                          GREEN_LED_PIN,
                          GPIO_PIN_SET);

        /* Red LED OFF */
        HAL_GPIO_WritePin(RED_LED_PORT,
                          RED_LED_PIN,
                          GPIO_PIN_RESET);


    }
    else
    {
        /* Green LED OFF */
        HAL_GPIO_WritePin(GREEN_LED_PORT,
                          GREEN_LED_PIN,
                          GPIO_PIN_RESET);

        /* Red LED ON */
        HAL_GPIO_WritePin(RED_LED_PORT,
                          RED_LED_PIN,
                          GPIO_PIN_SET);


    }
}
