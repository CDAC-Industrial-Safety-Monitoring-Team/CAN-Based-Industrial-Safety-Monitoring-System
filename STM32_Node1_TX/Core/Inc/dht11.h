/*
 * dht11.h
 *
 *
 *      Author: Moeen Sheikh
 */

#ifndef __DHT11_H__
#define __DHT11_H__

#include "common.h"

/**************** DHT11 Pin Configuration ****************/
#define DHT11_PORT     GPIOB
#define DHT11_PIN      GPIO_PIN_1

/**************** DHT11 APIs ****************/

void DHT11_Init(void);

HAL_StatusTypeDef DHT11_ReadData(SensorData_t *Sensor);

#endif /* __DHT11_H__ */
