#ifndef DRV_TIM_H
#define DRV_TIM_H

/* Includes ------------------------------------------------------------------*/

#include "tim.h"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/**
 * @brief TIM定时器回调函数数据类型
 *
 */
typedef void (*TIM_Call_Back)();

/**
 * @brief TIM定时器处理结构体
 *
 */
struct Struct_TIM_Manage_Object
{
    TIM_HandleTypeDef *TIM_Handler;
    TIM_Call_Back Callback_Function;
};

/* Exported variables --------------------------------------------------------*/


extern TIM_HandleTypeDef htim3;


extern struct Struct_TIM_Manage_Object TIM1_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM2_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM3_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM4_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM5_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM6_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM7_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM8_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM9_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM10_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM11_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM12_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM13_Manage_Object;
extern struct Struct_TIM_Manage_Object TIM14_Manage_Object;

/* Exported function declarations --------------------------------------------*/

void TIM_Init(TIM_HandleTypeDef *htim, TIM_Call_Back Callback_Function);

#endif