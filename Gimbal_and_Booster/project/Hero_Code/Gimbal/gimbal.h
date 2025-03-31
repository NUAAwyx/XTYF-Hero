#ifndef __GIMBAL_H
#define __GIMBAL_H

#include "dvc_bmi088.h"
#include "dvc_vofa.h"
#include "dvc_motor_DJI.h"
#include "dvc_motor_LK.h"
#include "master.h"

struct Struct_Gimbal
{
    float Pitch_Angle;

    float Yaw_Angle;
    float Yaw_Omega;
    
    int16_t Yaw_Control_Output;

    struct Struct_BMI088 BMI088;
    
    struct Struct_Motor_DJI Pitch_Motor;
    struct Struct_Motor_LK Yaw_Motor;
};

extern struct Struct_Gimbal Gimbal;

void Gimbal_Init();


void Gimbal_Control(float Pitch_Angle, int32_t Yaw_Speed);




#endif