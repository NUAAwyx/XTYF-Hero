#ifndef __DRV_CAN_H
#define __DRV_CAN_H

#include "can.h"

/**
 * @brief CAN接收的信息结构体
 *
 */
struct Struct_CAN_Rx_Buffer
{
    CAN_RxHeaderTypeDef Header;
    uint8_t Data[8];
};

/**
 * @brief CAN通信接收回调函数数据类型
 *
 */
typedef void (*CAN_Call_Back)(struct Struct_CAN_Rx_Buffer *);

/**
 * @brief CAN通信处理结构体
 *
 */
struct Struct_CAN_Manage_Object
{
    CAN_HandleTypeDef *CAN_Handler;
    struct Struct_CAN_Rx_Buffer Rx_Buffer;
    CAN_Call_Back Callback_Function;
};

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

extern struct Struct_CAN_Manage_Object CAN1_Manage_Object;
extern struct Struct_CAN_Manage_Object CAN2_Manage_Object;

extern uint8_t CAN1_0x1fe_Tx_Data[8];
extern uint8_t CAN1_0x1ff_Tx_Data[8];
extern uint8_t CAN1_0x200_Tx_Data[8];
extern uint8_t CAN1_0x2fe_Tx_Data[8];

extern uint8_t CAN1_0x141_Tx_Data[8];

extern uint8_t CAN2_0x1fe_Tx_Data[8];
extern uint8_t CAN2_0x1ff_Tx_Data[8];
extern uint8_t CAN2_0x200_Tx_Data[8];
extern uint8_t CAN2_0x2fe_Tx_Data[8];

void CAN_Init(CAN_HandleTypeDef *hcan,CAN_Call_Back Callback_Function);

uint8_t CAN_Send_Data(CAN_HandleTypeDef *hcan, uint16_t ID, uint8_t *Data, uint16_t Length);


#endif