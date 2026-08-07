/*
 * mq2.h
 *
 *  Created on: 23-Jul-2026
 *      Author: shouri keer
 */

#ifndef MQ2_H
#define MQ2_H

#include "main.h"
#include "common.h"

#define MQ2_THRESHOLD    900

HAL_StatusTypeDef MQ2_Init(void);
HAL_StatusTypeDef MQ2_ReadData(SensorData_t *Sensor);

#endif
