/*
 * common.h
 *
 *  Created on: 18-Jul-2026
 *      Author:sunbeam
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/******************** CAN IDs ********************/
#define CAN_TX_ID          0x321
#define CAN_RX_ID          0x322

/**************** CAN Packet Index ****************/
#define CAN_STATUS_INDEX        0
#define CAN_TEMP_INDEX          1
#define CAN_HUMIDITY_INDEX      2
#define CAN_VIBRATION_L_INDEX   3
#define CAN_VIBRATION_H_INDEX   4
#define CAN_GAS_INDEX           5

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
    uint16_t GasRaw;
    uint8_t GasDetected;

    SystemStatus_t Status;

} SensorData_t;

#endif /* __COMMON_H__ */
