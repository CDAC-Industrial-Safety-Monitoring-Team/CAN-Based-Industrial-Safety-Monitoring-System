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

/* MQ2 Analog Threshold */
#define MQ2_THRESHOLD    1800

/* Function Prototypes */
HAL_StatusTypeDef MQ2_Init(void);
HAL_StatusTypeDef MQ2_ReadData(SensorData_t *Sensor);

#endif
