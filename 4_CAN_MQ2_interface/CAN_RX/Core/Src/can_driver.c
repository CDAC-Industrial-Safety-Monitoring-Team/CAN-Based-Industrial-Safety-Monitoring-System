/*
 * can_driver.c
 *
 *  
 *      Author: shouri keer
 */

#include "can_driver.h"

extern CAN_HandleTypeDef hcan1;

static CAN_RxHeaderTypeDef RxHeader;
static uint8_t RxData[8];

void CAN_Driver_Init(void)
{
	CAN_FilterTypeDef CANFilter;

	CANFilter.FilterActivation = ENABLE;
	CANFilter.FilterBank = 0;
	CANFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CANFilter.FilterIdHigh = 0x0000;
	CANFilter.FilterIdLow = 0x0000;
	CANFilter.FilterMaskIdHigh = 0x0000;
	CANFilter.FilterMaskIdLow = 0x0000;
	CANFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	CANFilter.FilterScale = CAN_FILTERSCALE_32BIT;

	if (HAL_CAN_ConfigFilter(&hcan1, &CANFilter) != HAL_OK)
	{
	    Error_Handler();
	}

	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
	    Error_Handler();
	}

}

HAL_StatusTypeDef CAN_ReceivePacket(SensorData_t *sensor)
{
    if(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0)
    {
        return HAL_ERROR;
    }

    if(HAL_CAN_GetRxMessage(&hcan1,
                            CAN_RX_FIFO0,
                            &RxHeader,
                            RxData) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sensor->Status      = RxData[CAN_STATUS_INDEX];
    sensor->Temperature = RxData[CAN_TEMP_INDEX];
    sensor->Humidity    = RxData[CAN_HUMIDITY_INDEX];

    sensor->Vibration =
        (uint16_t)(RxData[CAN_VIBRATION_L_INDEX] |
                  (RxData[CAN_VIBRATION_H_INDEX] << 8));

    sensor->GasDetected = RxData[CAN_GAS_INDEX];

    return HAL_OK;
}

