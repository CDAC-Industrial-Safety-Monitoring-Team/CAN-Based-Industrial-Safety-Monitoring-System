/*
 * common.h
 *
 *
 *  Author: Moeen Sheikh
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "main.h"
#include <math.h>

/************ MPU6050 Registers ************/

#define MPU6050_ADDR          (0x68 << 1)
#define MPU6050_PWR_MGMT1     0x6B
#define MPU6050_ACCEL_XOUT    0x3B

typedef struct
{
    int16_t Ax;
    int16_t Ay;
    int16_t Az;

    float Magnitude;
    float Vibration;

} SensorData_t;


#endif /* __COMMON_H__ */
