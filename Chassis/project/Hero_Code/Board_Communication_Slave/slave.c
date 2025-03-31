#include "slave.h"

struct Struct_Slave Slave;

void Slave_Board_Init()
{
    UART_Init(&huart6, Slave_Board_Callback,Data_Package_Receive_Max_Length);
}

void Slave_Data_Process(uint8_t *Buffer, uint16_t Length)
{
    for(int i = 0; i < Length; i++)
    {
        Slave.Data_Package_Receive[i] = (Buffer[2 * i + 1] << 8) | Buffer[2 * i];
    }
}


void Slave_Board_Callback(uint8_t *Buffer, uint16_t Length)
{
/*     for(int i = 0; i < Length; i++)
    {
        Slave.Data_Package_Receive[i] = Buffer[i];
    } */
    Slave_Data_Process(Buffer, Length);

}