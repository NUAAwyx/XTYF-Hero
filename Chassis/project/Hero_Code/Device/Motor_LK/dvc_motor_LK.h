#ifndef __DVC_MOTOR_LK_H
#define __DVC_MOTOR_LK_H

#include "drv_can.h"
#include "drv_math.h"

struct Struct_Motor_LK
{
    struct Struct_CAN_Manage_Object CAN_Manage_Object;

    int8_t temperature;
    int16_t iq;
    int16_t speed;
    uint16_t encoder;

    int32_t Angle;
};

extern struct Struct_Motor_LK Motor_LK;


void Motor_Get_Status_1();
void Motor_Clear_Error_Flag();
void Motor_Get_Status_2();
void Motor_Get_Status_3();
void Motor_Off();
void Motor_On();
void Motor_Stop();
void Motor_Baozhaqi_Control(int16_t baozhaqi);
void Motor_Torque_Control(int16_t iqControl);
void Motor_Speed_Control(int16_t iqControl, int32_t speed_control);
void Motor_Multi_Angle_Control_1(int32_t angle_control);
void Motor_Multi_Angle_Control_2(uint16_t max_speed, int32_t angle_control);
void Motor_Single_Angle_Control_1(uint8_t spinDirection, uint32_t angle_control);
void Motor_Single_Angle_Control_2(uint8_t spinDirection, uint16_t maxSpeed, uint32_t angle_control);
void Motor_Add_Location_Control_1(int32_t angleIncrement);
void Motor_Add_Location_Control_2(int32_t angleIncrement, uint32_t max_speed);
void Read_Control_Parameter(uint8_t controlParamID);
void Read_Encoder_Data();
void Set_Current_Location_To_ROM();
void Read_Multi_Angle();
void Read_Single_Angle();
void Set_Current_Location_Random_Angle(int32_t motorAngle);

void Motor_LK_Callback(struct Struct_CAN_Rx_Buffer *rx_buffer);


#endif