/*
 * safety_monitor.h
 *
 *
 *      Author: Moeen Sheikh
 */

#ifndef __SAFETY_MONITOR_H__
#define __SAFETY_MONITOR_H__

#include "common.h"
#include "mpu6050.h"
#include "dht11.h"

/* Update all sensor values and system status */
HAL_StatusTypeDef SafetyMonitor_Update(SensorData_t *Sensor);

#endif /* __SAFETY_MONITOR_H__ */
