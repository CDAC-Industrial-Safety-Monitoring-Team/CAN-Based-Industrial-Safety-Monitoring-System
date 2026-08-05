/*
 * mpu6050.c
 *
 *
 *      Author: Moeen Sheikh
 */

#include "mpu6050.h"

/* MPU6050 uses I2C1 configured in main.c */
extern I2C_HandleTypeDef hi2c1;

/*----------------------------------------------------------*/

void MPU6050_Init(void)
{
    uint8_t wakeup = 0;

    HAL_I2C_Mem_Write(&hi2c1,
                      MPU6050_ADDR,
                      MPU6050_PWR_MGMT1,
                      I2C_MEMADD_SIZE_8BIT,
                      &wakeup,
                      1,
                      HAL_MAX_DELAY);
}

/*----------------------------------------------------------*/

HAL_StatusTypeDef MPU6050_ReadRawData(SensorData_t *Sensor)
{
    uint8_t accel_data[6];

    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(&hi2c1,
                              MPU6050_ADDR,
                              MPU6050_ACCEL_XOUT,
                              I2C_MEMADD_SIZE_8BIT,
                              accel_data,
                              6,
                              HAL_MAX_DELAY);

    if(status != HAL_OK)
    {
        return status;
    }

    Sensor->Ax = (int16_t)((accel_data[0] << 8) | accel_data[1]);
    Sensor->Ay = (int16_t)((accel_data[2] << 8) | accel_data[3]);
    Sensor->Az = (int16_t)((accel_data[4] << 8) | accel_data[5]);

    return HAL_OK;
}

/*----------------------------------------------------------*/

void MPU6050_CalculateMagnitude(SensorData_t *Sensor)
{
    Sensor->Magnitude =
            sqrtf((float)Sensor->Ax * Sensor->Ax +
                  (float)Sensor->Ay * Sensor->Ay +
                  (float)Sensor->Az * Sensor->Az);
}

/*----------------------------------------------------------*/

void MPU6050_CalculateVibration(SensorData_t *Sensor)
{
    Sensor->Vibration =
            fabsf(Sensor->Magnitude - 16384.0f);
}
