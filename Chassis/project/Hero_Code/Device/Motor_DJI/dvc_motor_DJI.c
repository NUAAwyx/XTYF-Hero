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

        Motor_DJI_Power_Limit_Control(motor_dji);
    }

    motor_dji->Output_Data[0] = (int16_t)motor_dji->Output >> 8;
    motor_dji->Output_Data[1] = (int16_t)motor_dji->Output;
}

/**
 * @brief 估计功率值
 *
 * @param K_0 电机建模系数
 * @param K_1 电机建模系数
 * @param K_2 电机建模系数
 * @param A 电机建模系数
 * @param Current 电流
 * @param Omega 角速度
 * @return
 */
float power_calculate(float K_0, float K_1, float K_2, float A, float Current, float Omega)
{
    return (K_0 * Current * Omega + K_1 * Omega * Omega + K_2 * Current * Current + A);
}

/**
 * @brief 功率控制算法, 修改电流目标值
 *
 */
void Motor_DJI_Power_Limit_Control(struct Struct_Motor_DJI *motor_dji)
{
    // 计算功率估计值
    motor_dji->Power_Estimate = power_calculate(Power_K_0, Power_K_1, Power_K_2, Power_A, motor_dji->Output, motor_dji->Omega);

    // 若功率为正则考虑功率控制限制
    if (motor_dji->Power_Estimate > 0.0f)
    {
        if (motor_dji->Power_Factor >= 1.0f)
        {
            // 无需功率控制
        }
        else
        {
            // 需要功率控制

            // 根据功率估计公式解一元二次方程求电流值
            float a = Power_K_2;
            float b = Power_K_0 * motor_dji->Omega;
            float c = Power_A + Power_K_1 * motor_dji->Omega * motor_dji->Omega - motor_dji->Power_Factor * motor_dji->Power_Estimate;
            float delta, h;
            delta = b * b - 4 * a * c;
            if (delta < 0.0f)
            {
                // 无解
                motor_dji->Target_Current = 0.0f;
            }
            else
            {
                arm_sqrt_f32(delta, &h);
                float result_1, result_2;
                result_1 = (-b + h) / (2.0f * a);
                result_2 = (-b - h) / (2.0f * a);

                // 两个潜在的可行电流值, 取绝对值最小的那个
                if ((result_1 > 0.0f && result_2 < 0.0f) || (result_1 < 0.0f && result_2 > 0.0f))
                {
                    if ((motor_dji->Target_Current > 0.0f && result_1 > 0.0f) || (motor_dji->Target_Current < 0.0f && result_1 < 0.0f))
                    {
                        motor_dji->Target_Current = result_1;
                    }
                    else
                    {
                        motor_dji->Target_Current = result_2;
                    }
                }
                else
                {
                    if (Math_Abs(result_1) < Math_Abs(result_2))
                    {
                        motor_dji->Target_Current = result_1;
                    }
                    else
                    {
                        motor_dji->Target_Current = result_2;
                    }
                }
            }
        }
    }
}
