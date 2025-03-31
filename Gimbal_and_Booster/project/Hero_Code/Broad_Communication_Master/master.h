#ifndef __MASTER_H
#define __MASTER_H

#include "dvc_dr16.h"
#include "drv_usart.h"
#include "gimbal.h"

//#define Data_Package_Max_Length 256

struct Struct_Master
{
    int16_t Chassis_State;//底盘状态，0静止，1运动
    int16_t Booster_State;//拨弹盘状态，0静止，1运动
    //int16_t State;//L[0:8],R[9:15]
    int16_t Chassis_w;//底盘旋转速度
    int16_t Chassis_Vx_G;//云台视角x方向速度
    int16_t Chassis_Vy_G;//云台视角y方向速度
    int16_t Chassis_W_State;//小陀螺开关
    int16_t Gimbal_To_Chassis_Theta;//云台相对底盘的角度

    //int32_t Master_Data[20];

    int16_t Master_Data[20];
    uint8_t Master_Data_Num;
};

extern struct Struct_Master Master;

void Master_Data_Process(int16_t *Master_Data, uint8_t num);

void Master_Control();



#endif