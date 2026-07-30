/*
 * can.c
 *
 *  Created on: 25-Jun-2026
 *      Author: sunbeam
 */

#include "can.h"

/* Links to the CAN handle generated in main.c */
extern CAN_HandleTypeDef hcan1;

/* Internal variables to hold headers and arrays */
static CAN_TxHeaderTypeDef  TxHeader;
static CAN_RxHeaderTypeDef  RxHeader;
static uint8_t              TxData[4]; /* 4 bytes: status, temp, mq2, mag */
static uint8_t              RxData[4];
static uint32_t             TxMailbox;

static CAN_SensorFrame_t    rxFrame;
static volatile uint8_t     rxDataReady = 0;

/**
 * @brief Initializes the CAN headers, filters, and turns on interrupts.
 */
void MX_CAN1_Filter_Config(void)
{
    /* 1. Setup the basic Transmitter parameters */
    TxHeader.StdId              = SENSOR_CAN_ID; /* 0x123 */
    TxHeader.IDE                = CAN_ID_STD;
    TxHeader.RTR                = CAN_RTR_DATA;
    TxHeader.DLC                = 4;             /* Sending 4 bytes */
    TxHeader.TransmitGlobalTime = DISABLE;

    /* 2. Setup a wide-open Filter so loopback mode accepts everything */
    CAN_FilterTypeDef filter = {0};
    filter.FilterBank           = 0;
    filter.FilterMode           = CAN_FILTERMODE_IDMASK;
    filter.FilterScale          = CAN_FILTERSCALE_32BIT;
    filter.FilterFIFOAssignment = CAN_RX_FIFO0;
    filter.FilterActivation     = ENABLE;
    HAL_CAN_ConfigFilter(&hcan1, &filter);

    /* 3. Turn on the hardware interrupt and start the CAN network engine */
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_Start(&hcan1);
}

/**
 * @brief Simple transmitter. Puts the 4 values directly into the 4 array slots.
 */
HAL_StatusTypeDef CAN_N1_Transmit(uint8_t status, int16_t temp, uint16_t mq2, uint16_t mag)
{
    TxData[0] = status;
    TxData[1] = (uint8_t)temp; /* Puts lower byte directly into slot */
    TxData[2] = (uint8_t)mq2;
    TxData[3] = (uint8_t)mag;

    /* Wait if all transmission mailboxes are busy */
    while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0);

    return HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
}

/**
 * @brief This runs automatically behind the scenes whenever a loopback packet arrives.
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN1)
    {
        /* Grab the message safely out of the hardware register buffer */
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            if (RxHeader.StdId == SENSOR_CAN_ID)
            {
                /* Pull the single bytes directly back out */
                rxFrame.status      = RxData[0];
                rxFrame.temperature = RxData[1];
                rxFrame.mq2         = RxData[2];
                rxFrame.magnitude   = RxData[3];
                rxDataReady         = 1; /* Set flag to notify main loop */
            }
        }
    }
}

/**
 * @brief Checks if a frame arrived via interrupt. Copies it to main.c if ready.
 */
HAL_StatusTypeDef CAN_N2_GetFrame(CAN_SensorFrame_t *frame)
{
    if (rxDataReady == 0)
    {
        return HAL_ERROR; /* Nothing came in yet */
    }

    /* Copy the data over cleanly */
    *frame = rxFrame;
    rxDataReady = 0; /* Reset flag for next message */

    return HAL_OK;
}
