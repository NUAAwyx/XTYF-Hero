#include "dvc_motor_DJI.h"

void Motor_DJI_Init(struct Struct_Motor_DJI *motor_dji, enum Enum_Motor_type _Motor_Type,float gearbox_rate, float encoder_per_round)
{
    motor_dji->Gearbox_Rate = gearbox_rate;
    motor_dji->Motor_Type = _Motor_Type;
    motor_dji->Encoder_per_Round = encoder_per_round;
    motor_dji->Angle = 0;
    motor_dji->Omega = 0;
}

void Motor_DJI_Data_Process(struct Struct_Motor_DJI *motor_dji, struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    // 电机反馈数据处理
    motor_dji->encoder = (Rx_Buffer->Data[0] << 8) | Rx_Buffer->Data[1];
    motor_dji->omega = (Rx_Buffer->Data[2] << 8) | Rx_Buffer->Data[3];
    motor_dji->torque = (Rx_Buffer->Data[4] << 8) | Rx_Buffer->Data[5];
    motor_dji->temperature = (Rx_Buffer->Data[6] << 8);

    motor_dji->Angle = motor_dji->encoder / motor_dji->Encoder_per_Round * 360.0;

 
    //处理6020偏移量   
    if(motor_dji->Motor_Type == Pitch)
    {
        motor_dji->Angle -= 120;
        
        if(motor_dji->Angle < 0)
        {
            motor_dji->Angle += 360;
        }
    } 

    motor_dji->Angle = motor_dji->Angle / 360 * 2 * PI;
    
    //处理角度范围
    if(motor_dji->Angle > PI)
    {
        motor_dji->Angle -= 2 * PI;
    }

    motor_dji->Omega = motor_dji->omega * RPM_TO_RADPS / motor_dji->Gearbox_Rate;
}

void VOFA_to_Motor_DJI(struct Struct_Motor_DJI *motor_dji)
{
    switch (vofa_cmd_type)
    {
    case OP:
        PID_Set_Kp(&motor_dji->PID_Omega, vofa_cmd_data);
        break;
    case OI:
        PID_Set_Ki(&motor_dji->PID_Omega, vofa_cmd_data);
        break;
    case OD:
        PID_Set_Kd(&motor_dji->PID_Omega, vofa_cmd_data);
        break;
    case OF:
        PID_Set_Kf(&motor_dji->PID_Omega, vofa_cmd_data);
        break;
    case OT:
        PID_Set_Target(&motor_dji->PID_Omega, vofa_cmd_data);
        break;
    case AP:
        PID_Set_Kp(&motor_dji->PID_Angle, vofa_cmd_data);
        break;
    case AI:
        PID_Set_Ki(&motor_dji->PID_Angle, vofa_cmd_data);
        break;
    case AD:
        PID_Set_Kd(&motor_dji->PID_Angle, vofa_cmd_data);
        break;
    case AF:
        PID_Set_Kf(&motor_dji->PID_Angle, vofa_cmd_data);
        break;
    case AT:
        PID_Set_Target(&motor_dji->PID_Angle, vofa_cmd_data);
        break;    
    default:
        break;
    }
}


void Motor_DJI_Control(struct Struct_Motor_DJI *motor_dji)
{
    if(motor_dji->Motor_Type == GM6020)
    {
        PID_Set_Now(&motor_dji->PID_Angle, motor_dji->Angle);

        PID_Caculate(&motor_dji->PID_Angle);
    
        PID_Set_Target(&motor_dji->PID_Omega, motor_dji->PID_Angle.Output);

        PID_Set_Now(&motor_dji->PID_Omega, motor_dji->Omega);

        PID_Caculate(&motor_dji->PID_Omega);
    
        motor_dji->Output = PID_Get_Output(&motor_dji->PID_Omega);
    }
    else if(motor_dji->Motor_Type == M3508)
    {
        PID_Set_Target(&motor_dji->PID_Omega, motor_dji->PID_Omega.Target);

        PID_Set_Now(&motor_dji->PID_Omega, motor_dji->Omega);

        PID_Caculate(&motor_dji->PID_Omega);
    
        motor_dji->Output = PID_Get_Output(&motor_dji->PID_Omega);
    }

    else if(motor_dji->Motor_Type == M2006)
    {
        PID_Set_Target(&motor_dji->PID_Omega, motor_dji->PID_Omega.Target);

        PID_Set_Now(&motor_dji->PID_Omega, motor_dji->Omega);

        PID_Caculate(&motor_dji->PID_Omega);
    
        motor_dji->Output = PID_Get_Output(&motor_dji->PID_Omega);
    }

    else if(motor_dji->Motor_Type == Pitch)
    {
        PID_Set_Now(&motor_dji->PID_Angle, motor_dji->Angle);

        PID_Caculate(&motor_dji->PID_Angle);
    
        PID_Set_Target(&motor_dji->PID_Omega, motor_dji->PID_Angle.Output);

        PID_Set_Now(&motor_dji->PID_Omega, BMI088.Pitch_Omega);
        //PID_Set_Now(&motor_dji->PID_Omega, motor_dji->Omega);
        PID_Caculate(&motor_dji->PID_Omega);
    
        motor_dji->Output = PID_Get_Output(&motor_dji->PID_Omega);
    }

    else if(motor_dji->Motor_Type == Yaw)
    {
        PID_Set_Now(&motor_dji->PID_Angle, motor_dji->Angle);

        PID_Caculate(&motor_dji->PID_Angle);
    
        PID_Set_Target(&motor_dji->PID_Omega, motor_dji->PID_Angle.Output);

        PID_Set_Now(&motor_dji->PID_Omega, BMI088.Yaw_Omega);

        PID_Caculate(&motor_dji->PID_Omega);
    
        motor_dji->Output = PID_Get_Output(&motor_dji->PID_Omega);
    }

    motor_dji->Output_Data[0] = (int16_t)motor_dji->Output >> 8;
    motor_dji->Output_Data[1] = (int16_t)motor_dji->Output;
}

