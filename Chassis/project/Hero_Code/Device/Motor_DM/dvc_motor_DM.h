#ifndef __DVC_MOTOR_DM_H
#define __DVC_MOTOR_DM_H

#include "drv_can.h"
#include "drv_math.h"
#include "alg_pid.h"
#include "dvc_vofa.h"

/**
 * @brief 达妙电机状态
 *
 */
enum Enum_Motor_DM_Status
{
    Motor_DM_Status_DISABLE = 0,
    Motor_DM_Status_ENABLE,
};

enum Enum_Motor_DM_Control_Method
{
    Motor_DM_Control_Method_NORMAL_MIT = 0,
    Motor_DM_Control_Method_NORMAL_ANGLE_OMEGA,
    Motor_DM_Control_Method_NORMAL_OMEGA,
    Motor_DM_Control_Method_NORMAL_EMIT,
    Motor_DM_Control_Method_1_TO_4_CURRENT,
    Motor_DM_Control_Method_1_TO_4_OMEGA,
    Motor_DM_Control_Method_1_TO_4_ANGLE,
};

/**
 * @brief 达妙电机控制状态, 传统模式有效
 *
 */
enum Enum_Motor_DM_Control_Status_Normal
{
    Motor_DM_Control_Status_DISABLE = 0x0,
    Motor_DM_Control_Status_ENABLE,
    Motor_DM_Control_Status_OVERVOLTAGE = 0x8,
    Motor_DM_Control_Status_UNDERVOLTAGE,
    Motor_DM_Control_Status_OVERCURRENT,
    Motor_DM_Control_Status_MOS_OVERTEMPERATURE,
    Motor_DM_Control_Status_ROTOR_OVERTEMPERATURE,
    Motor_DM_Control_Status_LOSE_CONNECTION,
    Motor_DM_Control_Status_MOS_OVERLOAD,
};

/**
 * @brief 达妙电机传统模式源数据
 *
 */
struct Struct_Motor_DM_CAN_Rx_Data_Normal
{
    uint8_t CAN_ID : 4;
    uint8_t Control_Status_Enum : 4;
    uint16_t Angle_Reverse;
    uint8_t Omega_11_4;
    uint8_t Omega_3_0_Torque_11_8;
    uint8_t Torque_7_0;
    uint8_t MOS_Temperature;
    uint8_t Rotor_Temperature;
} __attribute__((packed));

/**
 * @brief 达妙电机常规源数据, MIT控制报文
 *
 */
struct Struct_Motor_DM_CAN_Tx_Data_Normal_MIT
{
    uint16_t Control_Angle_Reverse;
    uint8_t Control_Omega_11_4;
    uint8_t Control_Omega_3_0_K_P_11_8;
    uint8_t K_P_7_0;
    uint8_t K_D_11_4;
    uint8_t K_D_3_0_Control_Torque_11_8;
    uint8_t Control_Torque_7_0;
} __attribute__((packed));

/**
 * @brief 达妙电机经过处理的数据, 传统模式有效
 *
 */
struct Struct_Motor_DM_Rx_Data_Normal
{
    enum Enum_Motor_DM_Control_Status_Normal Control_Status;
    float Now_Angle;
    float Now_Omega;
    float Now_Torque;
    float Now_MOS_Temperature;
    float Now_Rotor_Temperature;
    uint32_t Pre_Encoder;
    int32_t Total_Encoder;
    int32_t Total_Round;
};

/**
 * @brief 达妙电机常规源数据, 位置速度控制报文
 *
 */
struct Struct_Motor_DM_CAN_Tx_Data_Normal_Angle_Omega
{
    float Control_Angle;
    float Control_Omega;
} __attribute__((packed));

struct Struct_Motor_DM
{

    struct PID PID_Angle; // 角度环PID
    struct PID PID_Omega; // 角速度环PID

    struct Struct_CAN_Manage_Object *CAN_Manage_Object; // CAN管理对象

    enum Enum_Motor_DM_Control_Status_Normal Control_Status;   // 控制状态

    // 收数据绑定的CAN ID, 与上位机驱动参数Master_ID保持一致
    uint16_t CAN_Rx_ID;
    // 发数据绑定的CAN ID, 是上位机驱动参数CAN_ID加上控制模式的偏移量
    uint16_t CAN_Tx_ID;
    // 最大位置, 与上位机控制幅值PMAX保持一致
    float Angle_Max;
    // 最大速度, 与上位机控制幅值VMAX保持一致
    float Omega_Max;
    // 最大扭矩, 与上位机控制幅值TMAX保持一致
    float Torque_Max;
    // 最大电流, 与上位机串口中上电打印电流保持一致
    float Current_Max;

    uint8_t Tx_Data[8]; // 发送缓冲区

    // 当前时刻的电机接收flag
    uint32_t Flag;
    // 前一时刻的电机接收flag
    uint32_t Pre_Flag;

    // 电机状态
    enum Enum_Motor_DM_Status Motor_DM_Status;
    // 电机对外接口信息
    struct Struct_Motor_DM_Rx_Data_Normal Rx_Data;

    // 写变量

    // 读写变量

    // 电机控制方式
    enum Enum_Motor_DM_Control_Method Motor_DM_Control_Method;

    // 角度, rad, 目标角度
    float Control_Angle;
    // 角速度, rad/s, MIT模式和速度模式是目标角速度, 其余模式是限幅
    float Control_Omega;
    // 扭矩, Nm, MIT模式是目标扭矩, EMIT模式无效, 其余模式是限幅
    float Control_Torque;
    // 电流, A, EMIT模式是限幅, 其余模式无效
    float Control_Current;
    // K_P, 0~500, MIT模式有效
    float K_P;
    // K_D, 0~5, MIT模式有效
    float K_D;

    int Gear_box; // 减速箱比例
};

extern struct Struct_Motor_DM Motor_DM;

void Motor_DM_Init(struct Struct_Motor_DM *Motor_DM, CAN_HandleTypeDef *hcan, uint8_t __CAN_Rx_ID, uint8_t __CAN_Tx_ID, enum Enum_Motor_DM_Control_Method __Motor_DM_Control_Method, float __Angle_Max, float __Omega_Max, float __Torque_Max, float __Current_Max);
void Motor_DM_Control(struct Struct_Motor_DM *Motor_DM);
void Output(struct Struct_Motor_DM *Motor_DM, uint8_t *Tx_Data);
void Data_Process(struct Struct_Motor_DM *Motor_DM);
void Motor_DM_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer);

void CAN_Send_Clear_Error(struct Struct_Motor_DM *Motor_DM);
void CAN_Send_Enter(struct Struct_Motor_DM *Motor_DM);
void CAN_Send_Exit(struct Struct_Motor_DM *Motor_DM);

void Set_Control_Angle(struct Struct_Motor_DM *Motor_DM, float __Control_Angle);
void Set_Control_Omega(struct Struct_Motor_DM *Motor_DM, float __Control_Omega);
void Set_Control_Torque(struct Struct_Motor_DM *Motor_DM, float __Control_Torque);
void Set_Control_Current(struct Struct_Motor_DM *Motor_DM, float __Control_Current);
void Set_K_P(struct Struct_Motor_DM *Motor_DM, float __K_P);
void Set_K_D(struct Struct_Motor_DM *Motor_DM, float __K_D);




#endif