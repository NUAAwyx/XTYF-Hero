#include "dvc_motor_DM.h"

struct Struct_Motor_DM Motor_DM;

// 清除电机错误信息, 传统模式有效
uint8_t DM_Motor_CAN_Message_Clear_Error[8] = {0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xfb};
// 使能电机, 传统模式有效
uint8_t DM_Motor_CAN_Message_Enter[8] = {0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xfc};
// 失能电机, 传统模式有效
uint8_t DM_Motor_CAN_Message_Exit[8] = {0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xfd};
// 保存当前电机位置为零点, 传统模式有效
uint8_t DM_Motor_CAN_Message_Save_Zero[8] = {0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xfe};


/**
 * @brief 电机初始化
 *
 * @param hcan 绑定的CAN总线
 * @param __CAN_Rx_ID 收数据绑定的CAN ID, 与上位机驱动参数Master_ID保持一致, 传统模式有效
 * @param __CAN_Tx_ID 发数据绑定的CAN ID, 是上位机驱动参数CAN_ID加上控制模式的偏移量, 传统模式有效
 * @param __Motor_DM_Control_Method 电机控制方式
 * @param __Angle_Max 最大位置, 与上位机控制幅值PMAX保持一致, 传统模式有效
 * @param __Omega_Max 最大速度, 与上位机控制幅值VMAX保持一致, 传统模式有效
 * @param __Torque_Max 最大扭矩, 与上位机控制幅值TMAX保持一致, 传统模式有效
 */
void Motor_DM_Init(struct Struct_Motor_DM *Motor_DM, CAN_HandleTypeDef *hcan, uint8_t __CAN_Rx_ID, uint8_t __CAN_Tx_ID, enum Enum_Motor_DM_Control_Method __Motor_DM_Control_Method, float __Angle_Max, float __Omega_Max, float __Torque_Max, float __Current_Max)
{
    if (hcan->Instance == CAN1)
    {
        Motor_DM->CAN_Manage_Object = &CAN1_Manage_Object;
    }
    else if (hcan->Instance == CAN2)
    {
        Motor_DM->CAN_Manage_Object = &CAN2_Manage_Object;
    }

    Motor_DM->CAN_Rx_ID = __CAN_Rx_ID;
    switch (__Motor_DM_Control_Method)
    {
    case (Motor_DM_Control_Method_NORMAL_MIT):
    {
        Motor_DM->CAN_Tx_ID = __CAN_Tx_ID;
        break;
    }
     case (Motor_DM_Control_Method_NORMAL_ANGLE_OMEGA):
    {
        Motor_DM->CAN_Tx_ID = __CAN_Tx_ID + 0x100;
        break;
    }
/*    case (Motor_DM_Control_Method_NORMAL_OMEGA):
    {
        CAN_Tx_ID = __CAN_Tx_ID + 0x200;
        break;
    }
    case (Motor_DM_Control_Method_NORMAL_EMIT):
    {
        CAN_Tx_ID = __CAN_Tx_ID + 0x300;
        break;
    } */
    }
    Motor_DM->Motor_DM_Control_Method = __Motor_DM_Control_Method;
    Motor_DM->Angle_Max = __Angle_Max;
    Motor_DM->Omega_Max = __Omega_Max;
    Motor_DM->Torque_Max = __Torque_Max;
    Motor_DM->Current_Max = __Current_Max;
}

/**
 * @brief 数据处理过程
 *
 */
void Data_Process(struct Struct_Motor_DM *Motor_DM)
{
    // 数据处理过程
    int32_t delta_encoder;
    uint16_t tmp_encoder, tmp_omega, tmp_torque;
    struct Struct_Motor_DM_CAN_Rx_Data_Normal *tmp_buffer = (struct Struct_Motor_DM_CAN_Rx_Data_Normal *)Motor_DM->CAN_Manage_Object->Rx_Buffer.Data;

    // 电机ID不匹配, 则不进行处理
    if(tmp_buffer->CAN_ID != (Motor_DM->CAN_Tx_ID & 0x0f))
    {
        return;
    }

    // 处理大小端
    Math_Endian_Reverse_16((void *)&tmp_buffer->Angle_Reverse, &tmp_encoder);
    tmp_omega = (tmp_buffer->Omega_11_4 << 4) | (tmp_buffer->Omega_3_0_Torque_11_8 >> 4);
    tmp_torque = ((tmp_buffer->Omega_3_0_Torque_11_8 & 0x0f) << 8) | (tmp_buffer->Torque_7_0);

    Motor_DM->Rx_Data.Control_Status = tmp_buffer->Control_Status_Enum;

    // 计算圈数与总角度值
    delta_encoder = tmp_encoder - Motor_DM->Rx_Data.Pre_Encoder;
    if (delta_encoder < -(1 << 15))
    {
        // 正方向转过了一圈
        Motor_DM->Rx_Data.Total_Round++;
    }
    else if (delta_encoder > (1 << 15))
    {
        // 反方向转过了一圈
        Motor_DM->Rx_Data.Total_Round--;
    }
    Motor_DM->Rx_Data.Total_Encoder = Motor_DM->Rx_Data.Total_Round * (1 << 16) + tmp_encoder - ((1 << 15) - 1);

    // 计算电机本身信息
    Motor_DM->Rx_Data.Now_Angle = (float)(Motor_DM->Rx_Data.Total_Encoder) / (float)((1 << 16) - 1) * Motor_DM->Angle_Max * 2.0f;
    Motor_DM->Rx_Data.Now_Omega = Math_Int_To_Float(tmp_omega, 0x7ff, (1 << 12) - 1, 0, Motor_DM->Omega_Max);
    Motor_DM->Rx_Data.Now_Torque = Math_Int_To_Float(tmp_torque, 0x7ff, (1 << 12) - 1, 0, Motor_DM->Torque_Max);
    Motor_DM->Rx_Data.Now_MOS_Temperature = tmp_buffer->MOS_Temperature + CELSIUS_TO_KELVIN;
    Motor_DM->Rx_Data.Now_Rotor_Temperature = tmp_buffer->Rotor_Temperature + CELSIUS_TO_KELVIN;

    // 存储预备信息
    Motor_DM->Rx_Data.Pre_Encoder = tmp_encoder;
}



void Output(struct Struct_Motor_DM *Motor_DM, uint8_t *Tx_Data)
{
    // 电机控制
    switch (Motor_DM->Motor_DM_Control_Method)
    {
    case (Motor_DM_Control_Method_NORMAL_MIT):
    {
        struct Struct_Motor_DM_CAN_Tx_Data_Normal_MIT *tmp_buffer = (struct Struct_Motor_DM_CAN_Tx_Data_Normal_MIT *)Tx_Data;

        uint16_t tmp_angle, tmp_omega, tmp_torque, tmp_k_p, tmp_k_d;

        tmp_angle = Math_Float_To_Int(Motor_DM->Control_Angle, 0, Motor_DM->Angle_Max, 0x7fff, (1 << 16) - 1);
        tmp_omega = Math_Float_To_Int(Motor_DM->Control_Omega, 0, Motor_DM->Omega_Max, 0x7ff, (1 << 12) - 1);
        tmp_torque = Math_Float_To_Int(Motor_DM->Control_Torque, 0, Motor_DM->Torque_Max, 0x7ff, (1 << 12) - 1);
        tmp_k_p = Math_Float_To_Int(Motor_DM->K_P, 0, 500.0f, 0, (1 << 12) - 1);
        tmp_k_d = Math_Float_To_Int(Motor_DM->K_D, 0, 5.0f, 0, (1 << 12) - 1);

        tmp_buffer->Control_Angle_Reverse = Math_Endian_Reverse_16(&tmp_angle, NULL);
        tmp_buffer->Control_Omega_11_4 = tmp_omega >> 4;
        tmp_buffer->Control_Omega_3_0_K_P_11_8 = ((tmp_omega & 0x0f) << 4) | (tmp_k_p >> 8);
        tmp_buffer->K_P_7_0 = tmp_k_p & 0xff;
        tmp_buffer->K_D_11_4 = tmp_k_d >> 4;
        tmp_buffer->K_D_3_0_Control_Torque_11_8 = ((tmp_k_d & 0x0f) << 4) | (tmp_torque >> 8);
        tmp_buffer->Control_Torque_7_0 = tmp_torque & 0xff;

        CAN_Send_Data(Motor_DM->CAN_Manage_Object->CAN_Handler, Motor_DM->CAN_Tx_ID, Tx_Data, 8);

        break;
    }
     case (Motor_DM_Control_Method_NORMAL_ANGLE_OMEGA):
    {
        struct Struct_Motor_DM_CAN_Tx_Data_Normal_Angle_Omega *tmp_buffer = (struct Struct_Motor_DM_CAN_Tx_Data_Normal_Angle_Omega *)Tx_Data;

        tmp_buffer->Control_Angle = Motor_DM->Control_Angle;
        tmp_buffer->Control_Omega = Motor_DM->Control_Omega;

        CAN_Send_Data(Motor_DM->CAN_Manage_Object->CAN_Handler, Motor_DM->CAN_Tx_ID, Tx_Data, 8);

        break;
    }
/*  case (Motor_DM_Control_Method_NORMAL_OMEGA):
    {
        Struct_Motor_DM_CAN_Tx_Data_Normal_Omega *tmp_buffer = (Struct_Motor_DM_CAN_Tx_Data_Normal_Omega *)Tx_Data;

        tmp_buffer->Control_Omega = Control_Omega;

        CAN_Send_Data(CAN_Manage_Object->CAN_Handler, CAN_Tx_ID, Tx_Data, 4);

        break;
    }
    case (Motor_DM_Control_Method_NORMAL_EMIT):
    {
        Struct_Motor_DM_CAN_Tx_Data_Normal_EMIT *tmp_buffer = (Struct_Motor_DM_CAN_Tx_Data_Normal_EMIT *)Tx_Data;

        tmp_buffer->Control_Angle = Control_Angle;
        tmp_buffer->Control_Omega = (uint16_t)(Control_Omega * 100.0f);
        tmp_buffer->Control_Current = (uint16_t)(Control_Current / Current_Max * 10000.0f);

        CAN_Send_Data(CAN_Manage_Object->CAN_Handler, CAN_Tx_ID, Tx_Data, 8);

        break;
    } */
    }
}

void Motor_DM_Control(struct Struct_Motor_DM *Motor_DM)
{
    if (Motor_DM->Rx_Data.Control_Status == Motor_DM_Status_ENABLE)
    {
        // 电机在线, 正常控制
        Math_Constrain(&Motor_DM->Control_Angle, -Motor_DM->Angle_Max, Motor_DM->Angle_Max);
        Math_Constrain(&Motor_DM->Control_Omega, -Motor_DM->Omega_Max, Motor_DM->Omega_Max);
        Math_Constrain(&Motor_DM->Control_Torque, -Motor_DM->Torque_Max, Motor_DM->Torque_Max);
        Math_Constrain(&Motor_DM->Control_Current, -Motor_DM->Current_Max, Motor_DM->Current_Max);
        Math_Constrain(&Motor_DM->K_P, 0.0f, 500.0f);
        Math_Constrain(&Motor_DM->K_D, 0.0f, 5.0f);

        Output(Motor_DM, Motor_DM->Tx_Data);
    }
    else if (Motor_DM->Rx_Data.Control_Status == Motor_DM_Status_DISABLE)
    {
        // 电机可能掉线, 使能电机
        CAN_Send_Enter(Motor_DM);
    }
    else
    {
        // 电机错误, 发送清除错误帧
        CAN_Send_Clear_Error(Motor_DM);
    }
}

void Motor_DM_Callback(struct Struct_CAN_Rx_Buffer *Rx_Buffer)
{
    Data_Process(&Motor_DM);
}

/**
 * @brief 发送清除错误信息
 *
 */
void CAN_Send_Clear_Error(struct Struct_Motor_DM *Motor_DM)
{
    CAN_Send_Data(Motor_DM->CAN_Manage_Object->CAN_Handler, Motor_DM->CAN_Tx_ID,    DM_Motor_CAN_Message_Clear_Error, 8);
}

/**
 * @brief 发送使能电机
 *
 */
void CAN_Send_Enter(struct Struct_Motor_DM *Motor_DM)
{
    CAN_Send_Data(Motor_DM->CAN_Manage_Object->CAN_Handler, Motor_DM->CAN_Tx_ID, DM_Motor_CAN_Message_Enter, 8);
}

/**
 * @brief 发送失能电机
 *
 */
void CAN_Send_Exit(struct Struct_Motor_DM *Motor_DM)
{
    CAN_Send_Data(Motor_DM->CAN_Manage_Object->CAN_Handler, Motor_DM->CAN_Tx_ID, DM_Motor_CAN_Message_Exit, 8);
}



/**
 * @brief 设定角度, rad, 目标角度
 *
 */
void Set_Control_Angle(struct Struct_Motor_DM *Motor_DM, float __Control_Angle)
{
    Motor_DM->Control_Angle = __Control_Angle;
}

/**
 * @brief 设定角速度, rad/s, MIT模式和速度模式是目标角速度, 其余模式是限幅
 *
 * @param __Control_Omega 角速度, rad/s, MIT模式和速度模式是目标角速度, 其余模式是限幅
 */
void Set_Control_Omega(struct Struct_Motor_DM *Motor_DM, float __Control_Omega)
{
    Motor_DM->Control_Omega = __Control_Omega;
}

/**
 * @brief 设定扭矩, Nm, MIT模式是目标扭矩, EMIT模式无效, 其余模式是限幅
 *
 */
void Set_Control_Torque(struct Struct_Motor_DM *Motor_DM, float __Control_Torque)
{
    Motor_DM->Control_Torque = __Control_Torque;
}

/**
 * @brief 设定电流, A, EMIT模式是限幅, 其余模式无效
 *
 */
void Set_Control_Current(struct Struct_Motor_DM *Motor_DM, float __Control_Current)
{
    Motor_DM->Control_Current = __Control_Current;
}

/**
 * @brief 设定K_P, 0~500, MIT模式有效
 *
 * @param __K_P K_P, 0~500, MIT模式有效
 */
void Set_K_P(struct Struct_Motor_DM *Motor_DM, float __K_P)
{
    Motor_DM->K_P = __K_P;
}

/**
 * @brief 设定K_D, 0~5, MIT模式有效
 *
 * @param __K_D K_D, 0~5, MIT模式有效
 */
void Set_K_D(struct Struct_Motor_DM *Motor_DM, float __K_D)
{
    Motor_DM->K_D = __K_D;
}
