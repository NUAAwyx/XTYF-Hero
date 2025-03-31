#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "dvc_motor_DJI.h"
#include "dvc_bmi088.h"
#include "slave.h"

//电池为前，前x，左y
//底盘电机id分别为：左上4，右上3，左下2，右下1

#define Chassis_Max_Velocity 2.0
#define Chassis_Max_W 2.0

#define wheel_radius 0.0762 //m，全向轮轮半径

#define wheel_distance 0.318 //m，车轮到底盘中心点的距离
#define wheel_distance_x 0.225 //m，车轮到底盘中心点的x方向距离
#define wheel_distance_y 0.225 //m，车轮到底盘中心点的y方向距离

#define RUN 1
#define STOP 0

/* enum Enum_Chassis_State
{
    Chassis_STOP = 0,
    Chassis_RUN = 1,
};

enum Enum_Chassis_Booster_State
{
    Booster_STOP = 0,
    Booster_RUN = 1,
};
 */

struct Struct_Chassis
{
    struct Struct_Motor_DJI wheel_motor[4];//3508

    struct Struct_BMI088 BMI088;

    uint8_t State;//底盘状态
    uint8_t Booster_State;//拨弹盘状态

    float Gimbal_To_Chassis_Theta_G;//云台相对于底盘的角度(角度)
    float Gimbal_To_Chassis_Theta_C;//云台相对于底盘的角度(弧度)

    float Vx_G;//云台视角底盘x方向速度
    float Vy_G;//云台视角底盘y方向速度
    float W_G;//底盘目标角速度
    
    float Vx_C;//底盘实际x方向速度
    float Vy_C;//底盘实际y方向速度
    float W_C;//底盘实际角速度

    float wheel_V[4];//底盘速度
    float wheel_Vx[4];//轮子x方向速度
    float wheel_Vy[4];//轮子y方向速度

    float wheel_motor_omega[4];//轮子转速

    float Power_Limit_Max;//最大功率限制

    float Power_Factor;//功率衰减因数
};

extern struct Struct_Chassis chassis;

void Chassis_Init();

void Inverse_Kinematics();

void Power_Limit_Control();


#endif