/*
 * mq2.c
 *
 *  Created on: 23-Jul-2026
 *      Author: shouri keer
 */

#include "mq2.h"

extern ADC_HandleTypeDef hadc1;

/*----------------------------------------------------------*/
/* MQ2 initialization                                       */
/*----------------------------------------------------------*/
HAL_StatusTypeDef MQ2_Init(void)
{
    return HAL_OK;
}

/*----------------------------------------------------------*/
/* Read MQ2 Analog Value Only                               */
/*----------------------------------------------------------*/
HAL_StatusTypeDef MQ2_ReadData(SensorData_t *Sensor)
{
    uint16_t adc_value;

    /* Start ADC conversion */
    HAL_ADC_Start(&hadc1);

    /* Wait for conversion */
    if(HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
        HAL_ADC_Stop(&hadc1);
        return HAL_ERROR;
    }

    /* Read ADC value */
    adc_value = HAL_ADC_GetValue(&hadc1);

    /* Stop ADC */
    HAL_ADC_Stop(&hadc1);

    /* Store ADC value */
    Sensor->GasRaw = adc_value;

    /*--------------------------------------------------
      Analog Threshold Detection
      ADC >= 1800  -> Gas Detected (Unsafe)
      ADC < 1800   -> Safe
    ---------------------------------------------------*/
    if(adc_value >= MQ2_THRESHOLD)
    {
        Sensor->GasDetected = 0;      // Gas Detected
    }
    else
    {
        Sensor->GasDetected = 1;      // Safe
    }

    return HAL_OK;
}
