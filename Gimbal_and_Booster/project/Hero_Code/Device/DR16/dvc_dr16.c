#include "dvc_dr16.h"

struct Struct_DR16 DR16;


void DR16_Init(UART_HandleTypeDef *huart)
{
    if(huart == &huart3)
    {
        DR16.DR16_UART_Manage_Object = &UART3_Manage_Object;

        UART_Init(huart,DR16_UART_RxCpltCallback,RC_FRAME_LENGTH);
    }
}

void DR16_UART_RxCpltCallback(uint8_t *Buffer, uint16_t Length)
{
    DR16_Data_Process(Buffer,Length);
}


void DR16_Data_Process(uint8_t *Buffer, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++) {
        DR16.DR16_UART_Rx_Buffer[i] = Buffer[i];
    }
    
    DR16.Right_X = (DR16.DR16_UART_Rx_Buffer[0] | (DR16.DR16_UART_Rx_Buffer[1] << 8)) & 0x07ff;        //!< Channel 0
    DR16.Right_Y = ((DR16.DR16_UART_Rx_Buffer[1] >> 3) | (DR16.DR16_UART_Rx_Buffer[2] << 5)) & 0x07ff; //!< Channel 1
    DR16.Left_Y = ((DR16.DR16_UART_Rx_Buffer[2] >> 6) | (DR16.DR16_UART_Rx_Buffer[3] << 2) |          //!< Channel 2
                          (DR16.DR16_UART_Rx_Buffer[4] << 10)) &0x07ff;
    DR16.Left_X = ((DR16.DR16_UART_Rx_Buffer[4] >> 1) | (DR16.DR16_UART_Rx_Buffer[5] << 7)) & 0x07ff; //!< Channel 3
    DR16.switch_R = ((DR16.DR16_UART_Rx_Buffer[5] >> 4) & 0x0003);                  //!< Switch left
    DR16.switch_L = ((DR16.DR16_UART_Rx_Buffer[5] >> 4) & 0x000C) >> 2;                       //!< Switch right
    DR16.mouse_x = DR16.DR16_UART_Rx_Buffer[6] | (DR16.DR16_UART_Rx_Buffer[7] << 8);                    //!< Mouse X axis
    DR16.mouse_y = DR16.DR16_UART_Rx_Buffer[8] | (DR16.DR16_UART_Rx_Buffer[9] << 8);                    //!< Mouse Y axis
    DR16.mouse_z = DR16.DR16_UART_Rx_Buffer[10] | (DR16.DR16_UART_Rx_Buffer[11] << 8);                  //!< Mouse Z axis
    DR16.mouse_press_l = DR16.DR16_UART_Rx_Buffer[12];                                  //!< Mouse Left Is Press ?
    DR16.mouse_press_r = DR16.DR16_UART_Rx_Buffer[13];                                  //!< Mouse Right Is Press ?
    DR16.key = DR16.DR16_UART_Rx_Buffer[14] | (DR16.DR16_UART_Rx_Buffer[15] << 8);                    //!< KeyBoard value
    DR16.Left_Front_Wheel = DR16.DR16_UART_Rx_Buffer[16] | (DR16.DR16_UART_Rx_Buffer[17] << 8);
 
    DR16.Right_X -= RC_CH_VALUE_OFFSET;
    DR16.Right_Y -= RC_CH_VALUE_OFFSET;
    DR16.Left_X -= RC_CH_VALUE_OFFSET;
    DR16.Left_Y -= RC_CH_VALUE_OFFSET;
    DR16.Left_Front_Wheel -= RC_CH_VALUE_OFFSET;

    //DR16.Left_Y *= -1;
    DR16.Right_X *= -1;
    //DR16.Left_Front_Wheel *= -1;
    
    DR16.w = (DR16.key & KEY_PRESSED_OFFSET_W) ? 1 : 0;
    DR16.s = (DR16.key & KEY_PRESSED_OFFSET_S) ? 1 : 0;
    DR16.a = (DR16.key & KEY_PRESSED_OFFSET_A) ? 1 : 0;
    DR16.d = (DR16.key & KEY_PRESSED_OFFSET_D) ? 1 : 0;
    DR16.shift = (DR16.key & KEY_PRESSED_OFFSET_SHIFT) ? 1 : 0;
    DR16.ctrl = (DR16.key & KEY_PRESSED_OFFSET_CTRL) ? 1 : 0;
    DR16.q = (DR16.key & KEY_PRESSED_OFFSET_Q) ? 1 : 0;
    DR16.e = (DR16.key & KEY_PRESSED_OFFSET_E) ? 1 : 0;
    DR16.r = (DR16.key & KEY_PRESSED_OFFSET_R) ? 1 : 0;
    DR16.f = (DR16.key & KEY_PRESSED_OFFSET_F) ? 1 : 0;
    DR16.g = (DR16.key & KEY_PRESSED_OFFSET_G) ? 1 : 0;
    DR16.z = (DR16.key & KEY_PRESSED_OFFSET_Z) ? 1 : 0;
    DR16.x = (DR16.key & KEY_PRESSED_OFFSET_X) ? 1 : 0;
    DR16.c = (DR16.key & KEY_PRESSED_OFFSET_C) ? 1 : 0;
    DR16.v = (DR16.key & KEY_PRESSED_OFFSET_V) ? 1 : 0;
    DR16.b = (DR16.key & KEY_PRESSED_OFFSET_B) ? 1 : 0;

    DR16.mouse_x_increment += DR16.mouse_x / 32678.0 * 2 * 3.14159 * 0.1;
    DR16.mouse_y_increment += DR16.mouse_y / 32678.0 * 2 * 3.14159 * 0.1;
}