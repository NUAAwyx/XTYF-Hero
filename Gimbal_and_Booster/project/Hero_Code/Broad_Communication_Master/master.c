#include "master.h"

struct Struct_Master Master;

void Master_Board_Init(UART_HandleTypeDef *huart, UART_Call_Back Callback_Function, uint16_t Rx_Buffer_Length)
{
    UART_Init(huart, Callback_Function, Rx_Buffer_Length);
}

void Master_Data_Process(int16_t *Master_Data, uint8_t num)
{
    for(int i = 0; i < num; i++)
    {
        for(int j = 2 * i; j < 2 * i + 2; j++)
        {
            UART6_Manage_Object.Tx_Buffer[j] = ((uint8_t*)Master_Data)[j];
        }
    }
}

void Master_Control()
{
    if(DR16.switch_L != 2)
    {
        Master.Chassis_State = 1;
    }
    else
    {
        Master.Chassis_State = 0;
    }

    if(DR16.switch_R == 1 || DR16.mouse_press_l == 1)
    {
        Master.Booster_State = 1;
    }
    else
    {
        Master.Booster_State = 0;
    }

    Master.Chassis_Vx_G = DR16.Left_X + (DR16.w - DR16.s) * 660;
    Master.Chassis_Vy_G = DR16.Left_Y + (-DR16.a + DR16.d) * 660;
    Master.Chassis_W_State = DR16.Left_Front_Wheel / 660 + DR16.shift;

    Master.Gimbal_To_Chassis_Theta = Motor_LK.Angle;

}

void Master_Board_Callback(uint8_t *Buffer, uint16_t Length)
{
    Master.Chassis_w = (Buffer[0] << 8) | Buffer[1];
}

