#ifndef __DVC_DR16_H
#define __DVC_DR16_H

#include "drv_usart.h"

#define RC_FRAME_LENGTH 18u

#define RC_UART_FRAME_LENGTH 36u

#define RC_CH_VALUE_MIN         ((uint16_t)364)
#define RC_CH_VALUE_OFFSET      ((uint16_t)1024)
#define RC_CH_VALUE_MAX         ((uint16_t)1684)

/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP                ((uint16_t)1)
#define RC_SW_MID               ((uint16_t)3)
#define RC_SW_DOWN              ((uint16_t)2)
#define switch_is_down(s)       (s == RC_SW_DOWN)
#define switch_is_mid(s)        (s == RC_SW_MID)
#define switch_is_up(s)         (s == RC_SW_UP)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W            ((uint16_t)1 << 0)
#define KEY_PRESSED_OFFSET_S            ((uint16_t)1 << 1)
#define KEY_PRESSED_OFFSET_A            ((uint16_t)1 << 2)
#define KEY_PRESSED_OFFSET_D            ((uint16_t)1 << 3)
#define KEY_PRESSED_OFFSET_SHIFT        ((uint16_t)1 << 4)
#define KEY_PRESSED_OFFSET_CTRL         ((uint16_t)1 << 5)
#define KEY_PRESSED_OFFSET_Q            ((uint16_t)1 << 6)
#define KEY_PRESSED_OFFSET_E            ((uint16_t)1 << 7)
#define KEY_PRESSED_OFFSET_R            ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F            ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G            ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z            ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X            ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C            ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V            ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B            ((uint16_t)1 << 15)
/* ----------------------- Data Struct ------------------------------------- */

struct Struct_DR16
{
    //遥控器数据
    int16_t Right_X;
    int16_t Right_Y;
    int16_t Left_X;
    int16_t Left_Y;
    int16_t Left_Front_Wheel;

    uint8_t switch_L;
    uint8_t switch_R;

    int16_t mouse_x;//鼠标x轴，负左正右
    int16_t mouse_y;//鼠标y轴，负左正右
    int16_t mouse_z;//鼠标z轴，负左正右
    uint8_t mouse_press_l;//鼠标左键，1为按下
    uint8_t mouse_press_r;//鼠标右键，1为按下
    uint8_t mouse_press_m;//鼠标中键，1为按下

    uint16_t key;//按键 W S A D Shift Ctrl Q E R F G Z X C V B

    //遥控器绑定串口   
    struct Struct_UART_Manage_Object *DR16_UART_Manage_Object;
    
    uint8_t DR16_UART_Rx_Buffer[RC_UART_FRAME_LENGTH];

} __attribute__((packed));

extern struct Struct_DR16 DR16;

void DR16_Init(UART_HandleTypeDef *huart);

void DR16_UART_RxCpltCallback(uint8_t *Buffer, uint16_t Length);

void DR16_Data_Process(uint8_t *Buffer, uint16_t Length);

#endif