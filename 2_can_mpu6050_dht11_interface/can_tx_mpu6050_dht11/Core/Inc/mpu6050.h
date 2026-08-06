/*
 * mpu6050.h
 *
 *  Created on: 19-Jul-2026
 *      Author: Moeen Sheikh
 */

#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "common.h"

/**************** MPU6050 APIs ****************/

void MPU6050_Init(void);

HAL_StatusTypeDef MPU6050_ReadRawData(SensorData_t *Sensor);

void MPU6050_CalculateMagnitude(SensorData_t *Sensor);

void MPU6050_CalculateVibration(SensorData_t *Sensor);

#endif /* __MPU6050_H__ */
