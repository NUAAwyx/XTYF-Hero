#ifndef __BOOSTER_DM_H
#define __BOOSTER_DM_H

#include "dvc_motor_DM.h"

/* struct Struct_Booster_DM
{
    struct Struct_Motor_DM Booster_Motor;
}

extern struct Struct_Booster_DM Booster_DM; */

void Booster_Init();

void Booster_Control_MIT(float Angle, float Omega, float Torque, float K_F,float K_D);

void Booster_Control_P_V(float p_des, float v_des);

void VOFA_to_Motor_DM(struct Struct_Motor_DM *motor_dm);

void Booster_Control(float angle);

#endif