/*
 * can.h
 *
 *  Created on: 25-Jun-2026
 *      Author: sunbeam
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_
//#ifndef __CAN_H
//#define __CAN_H

#include "main.h"

typedef struct {
    uint8_t status;
    int16_t temperature;
    uint16_t mq2;
    uint16_t magnitude;
} CAN_SensorFrame_t;

#define SENSOR_CAN_ID 0x123

void MX_CAN1_Filter_Config(void);
HAL_StatusTypeDef CAN_N1_Transmit(uint8_t status, int16_t temp, uint16_t mq2, uint16_t mag);
HAL_StatusTypeDef CAN_N2_GetFrame(CAN_SensorFrame_t *frame);



#endif /* INC_CAN_H_ */
