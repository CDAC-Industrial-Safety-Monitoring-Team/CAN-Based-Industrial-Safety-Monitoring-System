/*
 * common.h
 *
 *
 *      Author: Moeen Sheikh
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>



/******************** MPU6050 ********************/
#define MPU6050_ADDR       (0x68 << 1)
#define MPU6050_PWR_MGMT1  0x6B
#define MPU6050_ACCEL_XOUT 0x3B

/******************** System Status ********************/
typedef enum
{
    STATUS_NORMAL = 0,
    STATUS_EMERGENCY

} SystemStatus_t;

/******************** Thresholds ********************/
#define VIBRATION_THRESHOLD    1100

/******************** Sensor Data ********************/
typedef struct
{
    int16_t Ax;
    int16_t Ay;
    int16_t Az;

    float Magnitude;
    float Vibration;

    uint8_t Temperature;
    uint8_t Humidity;

    SystemStatus_t Status;

} SensorData_t;

#endif /* __COMMON_H__ */
