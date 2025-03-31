#ifndef __DVC_VOFA_H
#define __DVC_VOFA_H

#include "drv_usart.h"
#include <stdlib.h>

enum Enum_VOFA_cmd
{
    OP = 0,
    OI,
    OD,
    OF,
    OT,
    AP,
    AI,
    AD,
    AF,
    AT,
};

extern float vofa_cmd_data;
extern enum Enum_VOFA_cmd vofa_cmd_type;

extern float test_data[40];

void vofa_Init(UART_HandleTypeDef *huart, UART_Call_Back Callback_Function, uint16_t Rx_Buffer_Length);

void vofa_callback(uint8_t *Buffer, uint16_t Length);

void vofa_send(float *data, uint8_t num);

#endif