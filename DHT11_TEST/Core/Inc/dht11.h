/*
 * dht11.h
 *
 *  Created on: 28-Jul-2026
 *      Author: sunbeam
 */
#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"

void DHT11_Start(void);
uint8_t DHT11_Check_Response(void);
uint8_t DHT11_Read(void);
void Delay_us(uint16_t us);

extern uint8_t Rh_byte1;
extern uint8_t Rh_byte2;
extern uint8_t Temp_byte1;
extern uint8_t Temp_byte2;
extern uint8_t SUM;

#endif


