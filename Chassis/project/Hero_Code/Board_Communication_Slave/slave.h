#ifndef __SLAVE_H
#define __SLAVE_H

#include "drv_usart.h"
#include "drv_math.h"
#include "dvc_bmi088.h"

#define Data_Package_Receive_Max_Length 20
//#define Slave_Num 6

struct Struct_Slave
{
    int16_t Data_Package_Receive[Data_Package_Receive_Max_Length];
};

extern struct Struct_Slave Slave;

void Slave_Board_Init();

void Slave_Data_Process(uint8_t *Buffer, uint16_t Length);

void Slave_Board_Callback(uint8_t *Buffer, uint16_t Length);

#endif