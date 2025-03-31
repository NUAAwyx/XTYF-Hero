#include "chassis.h"

struct Struct_Chassis chassis;

void Chassis_Init()
{
    //chassis.Power_Limit_Max = refree.Power_Limit_Max;

    chassis.Power_Limit_Max = 60;

    PID_Init(&chassis.wheel_motor[0].PID_Omega, 3000, 0, 0, 0, 1000, 5000);
    Motor_DJI_Init(&chassis.wheel_motor[0], M3508, 19, 8192);

    PID_Init(&chassis.wheel_motor[1].PID_Omega, 3000, 0, 0, 0, 1000, 5000);
    Motor_DJI_Init(&chassis.wheel_motor[1], M3508, 19, 8192);

    PID_Init(&chassis.wheel_motor[2].PID_Omega, 3000, 0, 0, 0, 1000, 5000);
    Motor_DJI_Init(&chassis.wheel_motor[2], M3508, 19, 8192);

    PID_Init(&chassis.wheel_motor[3].PID_Omega, 3000, 0, 0, 0, 1000, 5000);
    Motor_DJI_Init(&chassis.wheel_motor[3], M3508, 19, 8192);

    //while(BMI088_Init()){};
    BMI088_Init();
}

void Inverse_Kinematics()
{
    chassis.W_C = chassis.BMI088.Yaw_Omega;

    chassis.Gimbal_To_Chassis_Theta_C = (chassis.Gimbal_To_Chassis_Theta_G + 0.007 * chassis.BMI088.Yaw_Omega) * DEG_TO_RAD;

    chassis.Vx_C = chassis.Vx_G * arm_cos_f32(chassis.Gimbal_To_Chassis_Theta_C) - chassis.Vy_G * arm_sin_f32(chassis.Gimbal_To_Chassis_Theta_C);
    chassis.Vy_C = chassis.Vx_G * arm_sin_f32(chassis.Gimbal_To_Chassis_Theta_C) + chassis.Vy_G * arm_cos_f32(chassis.Gimbal_To_Chassis_Theta_C);


    //底盘速度解算
    chassis.wheel_V[0] = chassis.Vx_C - chassis.Vy_C + chassis.W_G * (wheel_distance_x + wheel_distance_y);//左后
    chassis.wheel_V[1] = -chassis.Vx_C - chassis.Vy_C + chassis.W_G * (wheel_distance_x + wheel_distance_y);//右后
    chassis.wheel_V[2] = -chassis.Vx_C + chassis.Vy_C + chassis.W_G * (wheel_distance_x + wheel_distance_y);//右前
    chassis.wheel_V[3] = chassis.Vx_C + chassis.Vy_C + chassis.W_G * (wheel_distance_x + wheel_distance_y);//左前
    
    //电机转速解算(实际速度和电机速度相反，作用力与反作用力)
    chassis.wheel_motor_omega[0] = chassis.wheel_V[0] / wheel_radius;
    chassis.wheel_motor_omega[1] = chassis.wheel_V[1] / wheel_radius;
    chassis.wheel_motor_omega[2] = chassis.wheel_V[2] / wheel_radius;
    chassis.wheel_motor_omega[3] = chassis.wheel_V[3] / wheel_radius;

    //左前
    PID_Set_Target(&chassis.wheel_motor[3].PID_Omega, chassis.wheel_motor_omega[3]);
    
    //右前
    PID_Set_Target(&chassis.wheel_motor[2].PID_Omega, chassis.wheel_motor_omega[2]);
    
    //左后
    PID_Set_Target(&chassis.wheel_motor[0].PID_Omega, chassis.wheel_motor_omega[0]);

    //右后
    PID_Set_Target(&chassis.wheel_motor[1].PID_Omega, chassis.wheel_motor_omega[1]);
}

/**
 * @brief 轮向电机功率控制
 *
 * @param wheel_available_power 轮向电机可用功率
 * @param wheel_consume_power 轮向电机消耗功率
 * @return 功率因数
 */
float __Wheel_Power_Limit_Control(float wheel_available_power, float wheel_consume_power)
{
    if (wheel_consume_power <= wheel_available_power)
    {
        // 无需功率控制
        return (1.0f);
    }
    else
    {
        // 功率分配因子计算
        return (wheel_available_power / wheel_consume_power);
    }
}

void Power_Limit_Control()
{
    float available_power = chassis.Power_Limit_Max;
    float consume_power = 0.0f;
    float wheel_consume_power = 0.0f;
    float steer_power_single[4], wheel_power_single[4];

    for (int i = 0; i < 4; i++)
    {
        // 获取轮向电机功率估计值
        wheel_power_single[i] = chassis.wheel_motor[i].Power_Estimate;
        // 正功计入消耗, 负功计入补偿
        if (wheel_power_single[i] > 0)
        {
            consume_power += wheel_power_single[i];
            wheel_consume_power += wheel_power_single[i];
        }
        else
        {
            available_power += -wheel_power_single[i];
        }
    }

    chassis.Power_Factor = __Wheel_Power_Limit_Control(available_power, wheel_consume_power);
    
    for (int i = 0; i < 4; i++)
    {
        if (wheel_power_single[i] > 0)
        {
            chassis.wheel_motor[i].Power_Factor = chassis.Power_Factor;
        }
        else
        {
            chassis.wheel_motor[i].Power_Factor = 1.0f;
        }
    }
}
