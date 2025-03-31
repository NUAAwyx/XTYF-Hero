#include "booster_dm.h"

//struct Struct_Booster_DM Booster_DM;

void Booster_Init()
{
    PID_Init(&Motor_DM.PID_Angle, 5, 0, 0, 3, 0, 5);
    PID_Init(&Motor_DM.PID_Omega, 5, 0, 0, 0, 0, 5);
    Motor_DM_Init(&Motor_DM, &hcan1, 0x00, 0x01, Motor_DM_Control_Method_NORMAL_MIT, 12.5f, 45.0f, 18.0f, 1000.0f);
    
    //Motor_DM_Init(&Motor_DM, &hcan1, 0x00, 0x01, Motor_DM_Control_Method_NORMAL_ANGLE_OMEGA, 12.5f, 45.0f, 18.0f, 1000.0f);
}

void Booster_Control_MIT(float Angle, float Omega, float Torque, float K_F,float K_D)
{
    Set_Control_Angle(&Motor_DM, Angle);
    Set_Control_Omega(&Motor_DM, Omega);
    Set_Control_Torque(&Motor_DM, Torque);

    Set_K_P(&Motor_DM, K_F);
    Set_K_D(&Motor_DM, K_D);
    Motor_DM_Control(&Motor_DM);
}

void Booster_Control_P_V(float p_des, float v_des)
{
    Set_Control_Angle(&Motor_DM, p_des);
    Set_Control_Omega(&Motor_DM, v_des);

    Motor_DM_Control(&Motor_DM);
}

void VOFA_to_Motor_DM(struct Struct_Motor_DM *motor_dm)
{
    switch (vofa_cmd_type)
    {
    case OP:
        PID_Set_Kp(&motor_dm->PID_Omega, vofa_cmd_data);
        break;
    case OI:
        PID_Set_Ki(&motor_dm->PID_Omega, vofa_cmd_data);
        break;
    case OD:
        PID_Set_Kd(&motor_dm->PID_Omega, vofa_cmd_data);
        break;
    case OF:
        PID_Set_Kf(&motor_dm->PID_Omega, vofa_cmd_data);
        break;
    case OT:
        PID_Set_Target(&motor_dm->PID_Omega, vofa_cmd_data);
        break;
    case AP:
        PID_Set_Kp(&motor_dm->PID_Angle, vofa_cmd_data);
        break;
    case AI:
        PID_Set_Ki(&motor_dm->PID_Angle, vofa_cmd_data);
        break;
    case AD:
        PID_Set_Kd(&motor_dm->PID_Angle, vofa_cmd_data);
        break;
    case AF:
        PID_Set_Kf(&motor_dm->PID_Angle, vofa_cmd_data);
        break;
    case AT:
        PID_Set_Target(&motor_dm->PID_Angle, vofa_cmd_data);
        break;    
    default:
        break;
    }
}

void Booster_Control(float angle)
{
    PID_Set_Target(&Motor_DM.PID_Angle, angle);

    PID_Set_Now(&Motor_DM.PID_Angle, Motor_DM.Rx_Data.Now_Angle);

    PID_Caculate(&Motor_DM.PID_Angle);

    PID_Set_Target(&Motor_DM.PID_Omega, Motor_DM.PID_Angle.Output);

    PID_Set_Now(&Motor_DM.PID_Omega, Motor_DM.Rx_Data.Now_Omega);

    PID_Caculate(&Motor_DM.PID_Omega);

    float Output = PID_Get_Output(&Motor_DM.PID_Omega);
    
    Booster_Control_MIT(0, 0, Output, 0, 0);

    //Booster_Control_P_V(angle, omega);
}