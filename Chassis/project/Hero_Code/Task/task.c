#include "task.h"

float angle;

void CAN1_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    Motor_DM_Callback(Rx_Buffer);
    // VOFA_to_Motor_DM(&Motor_DM);
}

void CAN2_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    if (Rx_Buffer->Header.StdId == 0x201)
    {
        Motor_DJI_Data_Process(&chassis.wheel_motor[0], Rx_Buffer);
        // VOFA_to_Motor_DJI(&chassis.wheel_motor[0]);
    }
    else if (Rx_Buffer->Header.StdId == 0x202)
    {
        Motor_DJI_Data_Process(&chassis.wheel_motor[1], Rx_Buffer);
        // VOFA_to_Motor_DJI(&chassis.wheel_motor[1]);
    }
    else if (Rx_Buffer->Header.StdId == 0x203)
    {
        Motor_DJI_Data_Process(&chassis.wheel_motor[2], Rx_Buffer);
        // VOFA_to_Motor_DJI(&chassis.wheel_motor[2]);
    }
    else if (Rx_Buffer->Header.StdId == 0x204)
    {
        Motor_DJI_Data_Process(&chassis.wheel_motor[3], Rx_Buffer);
        // VOFA_to_Motor_DJI(&chassis.wheel_motor[3]);
    }
}


void Slave_Task()
{
    chassis.State = Slave.Data_Package_Receive[0];
    chassis.Booster_State = Slave.Data_Package_Receive[1];
    chassis.Vx_G = Slave.Data_Package_Receive[2] / 660.0 * Chassis_Max_Velocity;
    chassis.Vy_G = Slave.Data_Package_Receive[3] / 660.0 * Chassis_Max_Velocity;
    chassis.W_G = Slave.Data_Package_Receive[4] * Chassis_Max_W;

    chassis.Gimbal_To_Chassis_Theta_G = -Slave.Data_Package_Receive[5];

/*     BMI088_read(&BMI088);

    data = BMI088.Yaw_Omega * 1000;

    UART_Send_Data(&huart6, (uint8_t *)&data, 2); */
}

void Chassis_Control()
{
    Inverse_Kinematics();

    Power_Limit_Control();

    Motor_DJI_Control(&chassis.wheel_motor[0]);
    CAN2_0x200_Tx_Data[0] = chassis.wheel_motor[0].Output_Data[0];
    CAN2_0x200_Tx_Data[1] = chassis.wheel_motor[0].Output_Data[1];

    Motor_DJI_Control(&chassis.wheel_motor[1]);
    CAN2_0x200_Tx_Data[2] = chassis.wheel_motor[1].Output_Data[0];
    CAN2_0x200_Tx_Data[3] = chassis.wheel_motor[1].Output_Data[1];

    Motor_DJI_Control(&chassis.wheel_motor[2]);
    CAN2_0x200_Tx_Data[4] = chassis.wheel_motor[2].Output_Data[0];
    CAN2_0x200_Tx_Data[5] = chassis.wheel_motor[2].Output_Data[1];

    Motor_DJI_Control(&chassis.wheel_motor[3]);
    CAN2_0x200_Tx_Data[6] = chassis.wheel_motor[3].Output_Data[0];
    CAN2_0x200_Tx_Data[7] = chassis.wheel_motor[3].Output_Data[1];

    CAN_Send_Data(&hcan2, 0x200, CAN2_0x200_Tx_Data, 8);

    /*     test_data[0] = chassis.wheel_motor[0].PID_Omega.Target;
        test_data[1] = chassis.wheel_motor[0].Omega;

        vofa_send(test_data, 2); */
}

void Chassis_Task()
{
    BMI088_read(&chassis.BMI088);

    if (chassis.State == RUN)
    {
        Chassis_Control();
    }
}

void Booster_Task()
{
    if (chassis.Booster_State == RUN)
    {
        Booster_Control(angle);

        angle += 0.89;
    }
    else
    {
        chassis.Booster_State = STOP;
        Booster_Control_MIT(0, 0, 0, 0, 0);
    }

    /*     test_data[0] = Motor_DM.PID_Angle.Target;
        test_data[1] = Motor_DM.Rx_Data.Now_Angle;

        vofa_send(test_data, 2); */
}

void TIM3_Callback()
{
    Slave_Task();
    Chassis_Task();
    Booster_Task();
}

void Task_Init()
{
    CAN_Init(&hcan1, CAN1_Callback);
    CAN_Init(&hcan2, CAN2_Callback);

    TIM_Init(&htim3, TIM3_Callback);

    DR16_Init(&huart3);
    // vofa_Init(&huart6, vofa_callback, 20);
    Slave_Board_Init();

    Chassis_Init();
    Booster_Init();

    HAL_TIM_Base_Start_IT(&htim3);
}
