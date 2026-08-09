/*
 * can_driver.c
 *
 *  Created on: 19-Jul-2026
 *      Author: shouri keer
 *
 *  Description:
 *      CAN Driver Module
 */

#include "can_driver.h"

/* CAN Handle from main.c */
extern CAN_HandleTypeDef hcan1;

/* CAN Header */
static CAN_TxHeaderTypeDef TxHeader;
static uint32_t TxMailbox;
static uint8_t TxData[8];

/* CAN Filter */
static CAN_FilterTypeDef CAN_Filter;

/*----------------------------------------------------------*/

void CAN_Driver_Init(void)
{
    /* Configure CAN Filter */
    CAN_Filter.FilterBank = 0;
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;

    CAN_Filter.FilterIdHigh = 0x0000;
    CAN_Filter.FilterIdLow = 0x0000;
    CAN_Filter.FilterMaskIdHigh = 0x0000;
    CAN_Filter.FilterMaskIdLow = 0x0000;

    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CAN_Filter.FilterActivation = ENABLE;

    HAL_CAN_ConfigFilter(&hcan1, &CAN_Filter);

    /* Start CAN */
    HAL_CAN_Start(&hcan1);

    /* Configure TX Header */
    TxHeader.StdId = CAN_TX_ID;
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = 6;
    TxHeader.TransmitGlobalTime = DISABLE;
}

/*----------------------------------------------------------*/

void CAN_SendPacket(const SensorData_t *sensor)
{
    uint16_t vib = (uint16_t)sensor->Vibration;

    TxData[CAN_STATUS_INDEX] = sensor->Status;
    TxData[CAN_TEMP_INDEX] = sensor->Temperature;
    TxData[CAN_HUMIDITY_INDEX] = sensor->Humidity;

    TxData[CAN_VIBRATION_L_INDEX] = vib & 0xFF;
    TxData[CAN_VIBRATION_H_INDEX] = (vib >> 8) & 0xFF;

    TxData[CAN_GAS_INDEX] = sensor->GasDetected;

    if(HAL_CAN_AddTxMessage(&hcan1,
                            &TxHeader,
                            TxData,
                            &TxMailbox) != HAL_OK)
    {
        return;
    }

    while(HAL_CAN_IsTxMessagePending(&hcan1, TxMailbox));
}
