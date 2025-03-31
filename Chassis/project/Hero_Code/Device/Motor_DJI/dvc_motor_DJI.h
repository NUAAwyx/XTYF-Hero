#ifndef __DVC_MOTOR_DJI_H
#define __DVC_MOTOR_DJI_H

#include "drv_can.h"
#include "drv_math.h"
#include "dvc_vofa.h"
#include "alg_pid.h"
#include "dvc_bmi088.h"

// 电流到输出的转化系数
#define Current_To_Out 16384.0f / 20.0f

/* // 功率衰减因数
#define Power_Factor 1.0f */

// 理论最大输出电流
#define Theoretical_Output_Current_Max 20.0f

// 功率计算系数
#define Power_K_0 0.2962f
#define Power_K_1 0.0000f
#define Power_K_2 0.1519f
#define Power_A 1.3544f

enum Enum_Motor_type
{
    GM6020 = 0,
    M3508 = 1,
    M2006 = 2,
    Pitch = 3,
    Yaw = 4,
};

struct Struct_Motor_DJI
{
    enum Enum_Motor_type Motor_Type; // 电机类型

    struct Struct_CAN_Manage_Object Motor_CAN_Manage_Object; // 电机CAN管理对象

    int16_t encoder;     // 电机反馈机械角度(编码器值)
    int16_t omega;       // 电机反馈转速：RPM
    int16_t torque;      // 电机反馈实际电流
    int16_t temperature; // 电机反馈温度

    float Angle; // 电机解算后角度：rad
    float Omega; // 电机解算后转速：rad/s

    float Gearbox_Rate;      // 电机减速比
    float Encoder_per_Round; // 电机编码器每圈最大值

    float Output;           // 电机输出电流
    uint8_t Output_Data[2]; // 电机输出数据

    struct PID PID_Omega; // 电机速度环PID
    struct PID PID_Angle; // 电机角度环PID

    // 目标的角度, rad
    float Target_Angle;
    // 目标的速度, rad/s
    float Target_Omega;
    // 目标的电流
    float Target_Current;
    // 前馈的速度, rad/s
    float Feedforward_Omega;
    // 前馈的电流, A
    float Feedforward_Current;
    // 下一时刻的功率估计值, W
    float Power_Estimate;
    // 功率衰减因数
    float Power_Factor;

};

// 电机初始化函数
void Motor_DJI_Init(struct Struct_Motor_DJI *motor_dji, enum Enum_Motor_type _Motor_Type, float gearbox_rate, float encoder_per_round);

// 电机反馈数据解算函数
void Motor_DJI_Data_Process(struct Struct_Motor_DJI *motor_dji, struct Struct_CAN_Rx_Buffer *Rx_Buffer);

// VOFA指令转换为电机控制函数
void VOFA_to_Motor_DJI(struct Struct_Motor_DJI *motor_dji);

void Motor_DJI_Control(struct Struct_Motor_DJI *motor_dji);

void Motor_DJI_Power_Limit_Control(struct Struct_Motor_DJI *motor_dji);

#endif
