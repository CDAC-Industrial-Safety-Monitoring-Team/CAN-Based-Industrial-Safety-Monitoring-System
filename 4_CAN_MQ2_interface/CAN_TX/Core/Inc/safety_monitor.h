/*
 * safety_monitor.h
 *
 *  Created on: 19-Jul-2026
 *      Author: Moeen Sheikh
 */

#ifndef __SAFETY_MONITOR_H__
#define __SAFETY_MONITOR_H__

#include "common.h"
#include "mpu6050.h"
#include "dht11.h"
#include "mq2.h"

/* Update all sensor values and system status */
HAL_StatusTypeDef SafetyMonitor_Update(SensorData_t *Sensor);

#endif /* __SAFETY_MONITOR_H__ */
