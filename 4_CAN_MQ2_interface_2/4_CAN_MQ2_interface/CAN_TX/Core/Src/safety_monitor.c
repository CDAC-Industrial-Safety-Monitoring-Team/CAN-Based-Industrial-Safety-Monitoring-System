/*
 * safety_monitor.c
 *
 *  Created on: 19-Jul-2026
 *      Author: Moeen Sheikh
 */

#include "safety_monitor.h"

HAL_StatusTypeDef SafetyMonitor_Update(SensorData_t *Sensor)
{
    /* Read MPU6050 Data */
    if (MPU6050_ReadRawData(Sensor) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Calculate Magnitude */
    MPU6050_CalculateMagnitude(Sensor);

    /* Calculate Vibration */
    MPU6050_CalculateVibration(Sensor);

    /* Read DHT11 Data */
    if (DHT11_ReadData(Sensor) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Read MQ2 Gas Data */
    if (MQ2_ReadData(Sensor) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Decision Logic */
    if ((Sensor->Vibration > VIBRATION_THRESHOLD) ||
        (Sensor->GasDetected == 0))
    {
        Sensor->Status = STATUS_EMERGENCY;
    }
    else
    {
        Sensor->Status = STATUS_NORMAL;
    }

    return HAL_OK;
}
