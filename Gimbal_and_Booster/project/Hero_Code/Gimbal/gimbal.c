#include "gimbal.h"

struct Struct_Gimbal Gimbal;

void Pitch_Init()
{
    PID_Init(&Gimbal.Pitch_Motor.PID_Omega, 250, 0, 0, 1, 1000, 10000);
    PID_Init(&Gimbal.Pitch_Motor.PID_Angle, 200, 0, 10, 5, 1000, 10000);
    Motor_DJI_Init(&Gimbal.Pitch_Motor, Pitch, 1, 8192);

}

void Yaw_Init()
{
    PID_Init(&Motor_LK.PID_Omega, 2, 0, 0, 0.8, 1000, 10000);

    Motor_On();
}

void Gimbal_Init()
{
    while(BMI088_Init()){};

    Pitch_Init();

    Yaw_Init();
}

void Pitch_Control(float Pitch_Angle)
{
    PID_Set_Target(&Gimbal.Pitch_Motor.PID_Angle, Pitch_Angle);

    BMI088_read(&Gimbal.BMI088);

    Motor_DJI_Control(&Gimbal.Pitch_Motor);

    CAN2_0x2fe_Tx_Data[2] = Gimbal.Pitch_Motor.Output_Data[0];
    CAN2_0x2fe_Tx_Data[3] = Gimbal.Pitch_Motor.Output_Data[1];

    CAN_Send_Data(&hcan2, 0x2fe, CAN2_0x2fe_Tx_Data, 8);
}

void Yaw_Control(float Omega)
{
    PID_Set_Target(&Motor_LK.PID_Omega, Omega);
    PID_Set_Now(&Motor_LK.PID_Omega, Gimbal.BMI088.Yaw_Omega);
    PID_Caculate(&Motor_LK.PID_Omega);

    Gimbal.Yaw_Control_Output = (int16_t)(Motor_LK.PID_Omega.Output / 33.0 * 2048);

    Motor_Torque_Control(Gimbal.Yaw_Control_Output);
}

void Gimbal_Control(float Pitch_Angle, int32_t Speed)
{
    Pitch_Control(Pitch_Angle);
    Yaw_Control(Speed);
}
