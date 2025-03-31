#ifndef __BOOSTER_H
#define __BOOSTER_H

#include "dvc_motor_DJI.h"

struct Struct_Booser
{
    struct Struct_CAN_Manage_Object CAN_Manage_Object; 
    struct Struct_Motor_DJI Booster_Motor[2];
    
};

extern struct Struct_Booser Booster;

void Booster_Init();

void Booster_Control();


#endif