/*
 * can_driver.h
 *
 *  Created on: 19-Jul-2026
 *      Author: Moeen Sheikh
 */

#ifndef __CAN_DRIVER_H__
#define __CAN_DRIVER_H__

#include "common.h"

/**************** CAN Driver APIs ****************/

void CAN_Driver_Init(void);

void CAN_SendPacket(const SensorData_t *sensor);

#endif /* __CAN_DRIVER_H__ */
