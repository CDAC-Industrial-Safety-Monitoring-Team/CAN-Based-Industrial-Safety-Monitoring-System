/*
 * common.h
 *
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "main.h"

/* System Status */
typedef enum
{
    STATUS_NORMAL = 0,
    STATUS_EMERGENCY = 1

} SystemStatus_t;

/* Sensor Data Structure */
typedef struct
{
    uint8_t Temperature;
    uint8_t Humidity;
    float   Vibration;
    uint8_t GasDetected;
    SystemStatus_t Status;

} SensorData_t;

/* CAN Packet Index */
#define CAN_STATUS_INDEX        0
#define CAN_TEMP_INDEX          1
#define CAN_HUMIDITY_INDEX      2
#define CAN_VIBRATION_L_INDEX   3
#define CAN_VIBRATION_H_INDEX   4
#define CAN_GAS_INDEX           5

/* Green LED (PD0) */
#define GREEN_LED_PORT     GPIOD
#define GREEN_LED_PIN      GPIO_PIN_0

/* Red LED (PD1) */
#define RED_LED_PORT       GPIOD
#define RED_LED_PIN        GPIO_PIN_1

/* Buzzer (PB4) */
#define BUZZER_PORT        GPIOB
#define BUZZER_PIN         GPIO_PIN_4

#endif /* INC_COMMON_H_ */
