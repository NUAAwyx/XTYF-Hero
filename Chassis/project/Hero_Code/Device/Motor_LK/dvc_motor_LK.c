#include "dvc_motor_LK.h"

struct Struct_Motor_LK Motor_LK;

void Motor_Get_Status_1()
{
    CAN1_0x141_Tx_Data[0] = 0x9A;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Clear_Error_Flag()
{
    CAN1_0x141_Tx_Data[0] = 0x9B;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Get_Status_2()
{
    CAN1_0x141_Tx_Data[0] = 0x9C;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Get_Status_3()
{
    CAN1_0x141_Tx_Data[0] = 0x9D;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Off()
{
    CAN1_0x141_Tx_Data[0] = 0x80;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_On()
{
    CAN1_0x141_Tx_Data[0] = 0x88;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Stop()
{
    CAN1_0x141_Tx_Data[0] = 0x81;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Baozhaqi_Control(int16_t baozhaqi)
{
    CAN1_0x141_Tx_Data[0] = 0x8C;
    CAN1_0x141_Tx_Data[1] = baozhaqi;//0x00：抱闸器断电，刹车启动 0x01:抱闸器通电，刹车释放 0x10：读取抱闸器状态
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Torque_Control(int16_t iqControl)
{
    CAN1_0x141_Tx_Data[0] = 0xA1;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&iqControl);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&iqControl) + 1);
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Speed_Control(int16_t iqControl, int32_t speed_control)
{
    CAN1_0x141_Tx_Data[0] = 0xA2;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = *(uint8_t *)(&iqControl);
    CAN1_0x141_Tx_Data[3] = *((uint8_t *)(&iqControl)+1);
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&speed_control);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&speed_control) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(&speed_control) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(&speed_control) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Multi_Angle_Control_1(int32_t angle_control)
{
    CAN1_0x141_Tx_Data[0] = 0xA3;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&angle_control);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&angle_control) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(&angle_control) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(&angle_control) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Multi_Angle_Control_2(uint16_t max_speed, int32_t angle_control)
{
    CAN1_0x141_Tx_Data[0] = 0xA4;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = *(uint8_t *)(&max_speed);
    CAN1_0x141_Tx_Data[3] = *((uint8_t *)(&max_speed)+1);
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&angle_control);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&angle_control) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(&angle_control) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(&angle_control) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_Single_Angle_Control_1(uint8_t spinDirection, uint32_t angle_control)
{
    CAN1_0x141_Tx_Data[0] = 0xA5;
    CAN1_0x141_Tx_Data[1] = spinDirection;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&angle_control);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&angle_control) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(&angle_control) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(&angle_control) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}
void Motor_Single_Angle_Control_2(uint8_t spinDirection, uint16_t maxSpeed, uint32_t angle_control)
{
    CAN1_0x141_Tx_Data[0] = 0xA6;
    CAN1_0x141_Tx_Data[1] = spinDirection;
    CAN1_0x141_Tx_Data[2] = *(uint8_t *)(&maxSpeed);
    CAN1_0x141_Tx_Data[3] = *((uint8_t *)(&maxSpeed)+1);
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&angle_control);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(&angle_control) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(&angle_control) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(&angle_control) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Motor_Add_Location_Control_1(int32_t angleIncrement)
{
    CAN1_0x141_Tx_Data[0] = 0xA7;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(& angleIncrement);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(& angleIncrement) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(& angleIncrement) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(& angleIncrement) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Motor_Add_Location_Control_2(int32_t angleIncrement, uint32_t max_speed)
{
    CAN1_0x141_Tx_Data[0] = 0xA8;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = *(uint8_t *)(&max_speed);
    CAN1_0x141_Tx_Data[3] = *((uint8_t *)(&max_speed)+1);
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(& angleIncrement);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(& angleIncrement) + 1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(& angleIncrement) + 2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(& angleIncrement) + 3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Read_Control_Parameter(uint8_t controlParamID)
{
    CAN1_0x141_Tx_Data[0] = 0xC0;
    CAN1_0x141_Tx_Data[1] = controlParamID;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


/* void Write_Control_Parameter()
{
    CAN1_0x141_Tx_Data[0] = 0xC1;
    CAN1_0x141_Tx_Data[1] = controlParamID;
    CAN1_0x141_Tx_Data[2] = controlParamByte1;
    CAN1_0x141_Tx_Data[3] = controlParamByte2;
    CAN1_0x141_Tx_Data[4] = controlParamByte3;
    CAN1_0x141_Tx_Data[5] = controlParamByte4;
    CAN1_0x141_Tx_Data[6] = controlParamByte5;
    CAN1_0x141_Tx_Data[7] = controlParamByte6;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
} */


void Read_Encoder_Data()
{
    CAN1_0x141_Tx_Data[0] = 0x90;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Set_Current_Location_To_ROM()
{
    CAN1_0x141_Tx_Data[0] = 0x19;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Read_Multi_Angle()
{
    CAN1_0x141_Tx_Data[0] = 0x92;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}


void Read_Single_Angle()
{
    CAN1_0x141_Tx_Data[0] = 0x94;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = 0x00;
    CAN1_0x141_Tx_Data[5] = 0x00;
    CAN1_0x141_Tx_Data[6] = 0x00;
    CAN1_0x141_Tx_Data[7] = 0x00;

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Set_Current_Location_Random_Angle(int32_t motorAngle)
{
    CAN1_0x141_Tx_Data[0] = 0x95;
    CAN1_0x141_Tx_Data[1] = 0x00;
    CAN1_0x141_Tx_Data[2] = 0x00;
    CAN1_0x141_Tx_Data[3] = 0x00;
    CAN1_0x141_Tx_Data[4] = *(uint8_t *)(&motorAngle);
    CAN1_0x141_Tx_Data[5] = *((uint8_t *)(& motorAngle)+1);
    CAN1_0x141_Tx_Data[6] = *((uint8_t *)(& motorAngle)+2);
    CAN1_0x141_Tx_Data[7] = *((uint8_t *)(& motorAngle)+3);

    CAN_Send_Data(&hcan1, 0x141, CAN1_0x141_Tx_Data, 8);
}

void Motor_LK_Data_Process(struct Struct_CAN_Rx_Buffer *rx_buffer)
{
    Motor_LK.temperature = rx_buffer->Data[1];
    Motor_LK.iq = rx_buffer->Data[2] | (rx_buffer->Data[3] << 8);
    Motor_LK.speed = rx_buffer->Data[4] | (rx_buffer->Data[5] << 8);
    Motor_LK.encoder = rx_buffer->Data[6] | (rx_buffer->Data[7] << 8);

    //Motor_LK.Angle = Motor_LK.encoder / 16383 * 2 * PI;
    Motor_LK.Angle = Motor_LK.encoder / 16383 * 360;
}


void Motor_LK_Callback(struct Struct_CAN_Rx_Buffer *rx_buffer)
{
    Motor_LK_Data_Process(rx_buffer);
}
