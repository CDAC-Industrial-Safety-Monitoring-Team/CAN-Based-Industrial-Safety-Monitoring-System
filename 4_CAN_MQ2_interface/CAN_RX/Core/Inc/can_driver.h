/*
 * can_driver.h
 *
 *  
 *      Author: Shouri keer
 */

#ifndef __CAN_DRIVER_H__
#define __CAN_DRIVER_H__

#include "common.h"

void CAN_Driver_Init(void);

HAL_StatusTypeDef CAN_ReceivePacket(SensorData_t *sensor);

#endif /* INC_CAN_DRIVER_H_ */
