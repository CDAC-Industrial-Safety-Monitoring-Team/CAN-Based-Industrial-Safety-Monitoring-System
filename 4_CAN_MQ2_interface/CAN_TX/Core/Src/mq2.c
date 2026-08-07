/*
 * mq2.c
 *
 *  Created on: 23-Jul-2026
 *      Author: shouri keer
 */

#include "mq2.h"

extern ADC_HandleTypeDef hadc1;

/*----------------------------------------------------------*/
/* MQ2 initialization                                        */
/* GPIO is already configured by CubeMX                     */
/*----------------------------------------------------------*/
HAL_StatusTypeDef MQ2_Init(void)
{
    return HAL_OK;
}

/*----------------------------------------------------------*/
/* Read MQ2 analog + digital                                */
/*----------------------------------------------------------*/
HAL_StatusTypeDef MQ2_ReadData(SensorData_t *Sensor)
{
    uint16_t adc_value;
    GPIO_PinState gas;

    /* Start ADC conversion */
    HAL_ADC_Start(&hadc1);

    /* Wait until conversion completes */
    if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(&hadc1);
    }
    else
    {
        HAL_ADC_Stop(&hadc1);
        return HAL_ERROR;
    }

    /* Stop ADC */
    HAL_ADC_Stop(&hadc1);

    /* Store raw ADC value */
    Sensor->GasRaw = adc_value;

    /* Read digital output (PB0) */
    gas = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);

    /* Gas detection logic */
    if((adc_value > MQ2_THRESHOLD) ||
       (gas == GPIO_PIN_RESET))
    {
        Sensor->GasDetected = 0;      // Gas detected (Unsafe)
    }
    else
    {
        Sensor->GasDetected = 1;      // Safe
    }

    return HAL_OK;
}
