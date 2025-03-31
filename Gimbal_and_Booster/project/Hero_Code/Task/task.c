#include "task.h"

void CAN1_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    if (Rx_Buffer->Header.StdId == 0x141)
    {
        Motor_LK_Callback(Rx_Buffer);
        //VOFA_to_Motor_LK(&Motor_LK);
    }
}

void CAN2_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    if (Rx_Buffer->Header.StdId == 0x205)
    {
        Motor_DJI_Data_Process(&Booster.Booster_Motor[0], Rx_Buffer);
    }

    else if (Rx_Buffer->Header.StdId == 0x206)
    {
        Motor_DJI_Data_Process(&Booster.Booster_Motor[1], Rx_Buffer);
    }

    else if (Rx_Buffer->Header.StdId == 0x20A)
    {
        Motor_DJI_Data_Process(&Gimbal.Pitch_Motor, Rx_Buffer);
        // VOFA_to_Motor_DJI(&Gimbal.Pitch_Motor);
    }
}

void Gimbal_Task()
{
    Gimbal.Pitch_Angle = (DR16.Right_Y / 660.0 * 0.38 + 0.12) + (DR16.mouse_y_increment * 1000);

    Gimbal.Yaw_Omega = ((DR16.Right_X) / 660.0 * 2.0 + (Master.Chassis_W_State * 0.007)) + ((-DR16.mouse_x / 32678.0 ) * 2.0 * 1000 + (Master.Chassis_W_State * 0.7));

    Gimbal.Yaw_Angle = Motor_LK.Angle;

    if (Gimbal.Pitch_Angle > 0.5)
    {
        Gimbal.Pitch_Angle = 0.5;
    }
    else if (Gimbal.Pitch_Angle < -0.26)
    {
        Gimbal.Pitch_Angle = -0.26;
    }

    Gimbal_Control(Gimbal.Pitch_Angle, Gimbal.Yaw_Omega);

/*         test_data[0] = Gimbal.Yaw_Omega;
        test_data[1] = Gimbal.BMI088.Yaw_Omega;

        vofa_send(test_data, 2); */
}

void Booster_Task()
{
    if (DR16.switch_L == 1)
    {
        Booster_Control();
    }
}

void Master_Task()
{
    Master_Control();

    Master.Master_Data[0] = Master.Chassis_State;
    Master.Master_Data[1] = Master.Booster_State;
    Master.Master_Data[2] = Master.Chassis_Vx_G;
    Master.Master_Data[3] = Master.Chassis_Vy_G;
    Master.Master_Data[4] = Master.Chassis_W_State;
    Master.Master_Data[5] = Master.Gimbal_To_Chassis_Theta;

    Master.Master_Data_Num = 6;

    Master_Data_Process(Master.Master_Data, Master.Master_Data_Num);

    UART_Send_Data(&huart6, UART6_Manage_Object.Tx_Buffer, 2 * Master.Master_Data_Num);

    // UART_Send_Data(&huart6, (uint8_t*)Master.Master_Data, Master.Master_Data_Num);
}

void TIM3_Callback()
{
    Gimbal_Task();
    Booster_Task();
    Master_Task();
}

void Task_Init()
{
    CAN_Init(&hcan2, CAN2_Callback);
    CAN_Init(&hcan1, CAN1_Callback);

    TIM_Init(&htim3, TIM3_Callback);

    DR16_Init(&huart3);
    //vofa_Init(&huart6, vofa_callback, 20);

    Gimbal_Init();
    Booster_Init();

    HAL_TIM_Base_Start_IT(&htim3);
}
