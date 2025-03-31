#include "booster.h"

struct Struct_Booser Booster;

void Booster_Init()
{
    PID_Init(&Booster.Booster_Motor[0].PID_Omega, 3000, 0, 0, 0, 1000, 2500);
    Motor_DJI_Init(&Booster.Booster_Motor[0], M3508, 19, 8192);

    PID_Init(&Booster.Booster_Motor[1].PID_Omega, 3000, 0, 0, 0, 1000, 2500);
    Motor_DJI_Init(&Booster.Booster_Motor[1], M3508, 19, 8192);
}

void Booster_Control()
{
    PID_Set_Target(&Booster.Booster_Motor[0].PID_Omega, 1000);
    Motor_DJI_Control(&Booster.Booster_Motor[0]);

    PID_Set_Target(&Booster.Booster_Motor[1].PID_Omega, -1000);
    Motor_DJI_Control(&Booster.Booster_Motor[1]);

    CAN2_0x1ff_Tx_Data[0] = Booster.Booster_Motor[0].Output_Data[0];
    CAN2_0x1ff_Tx_Data[1] = Booster.Booster_Motor[0].Output_Data[1];
    CAN2_0x1ff_Tx_Data[2] = Booster.Booster_Motor[1].Output_Data[0];
    CAN2_0x1ff_Tx_Data[3] = Booster.Booster_Motor[1].Output_Data[1];

    CAN_Send_Data(&hcan2, 0x1ff, CAN2_0x1ff_Tx_Data, 8);
}

