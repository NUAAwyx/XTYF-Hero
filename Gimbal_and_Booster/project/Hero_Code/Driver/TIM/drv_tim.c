#include "drv_tim.h"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

struct Struct_TIM_Manage_Object TIM1_Manage_Object;
struct Struct_TIM_Manage_Object TIM2_Manage_Object;
struct Struct_TIM_Manage_Object TIM3_Manage_Object;
struct Struct_TIM_Manage_Object TIM4_Manage_Object;
struct Struct_TIM_Manage_Object TIM5_Manage_Object;
struct Struct_TIM_Manage_Object TIM6_Manage_Object;
struct Struct_TIM_Manage_Object TIM7_Manage_Object;
struct Struct_TIM_Manage_Object TIM8_Manage_Object;
struct Struct_TIM_Manage_Object TIM9_Manage_Object;
struct Struct_TIM_Manage_Object TIM10_Manage_Object;
struct Struct_TIM_Manage_Object TIM11_Manage_Object;
struct Struct_TIM_Manage_Object TIM12_Manage_Object;
struct Struct_TIM_Manage_Object TIM13_Manage_Object;
struct Struct_TIM_Manage_Object TIM14_Manage_Object;

/* Private function declarations ---------------------------------------------*/

/* function prototypes -------------------------------------------------------*/

/**
 * @brief 初始化TIM定时器
 *
 * @param htim 定时器编号
 * @param Callback_Function 处理回调函数
 */
void TIM_Init(TIM_HandleTypeDef *htim, TIM_Call_Back Callback_Function)
{
    if (htim->Instance == TIM1)
    {
        TIM1_Manage_Object.TIM_Handler = htim;
        TIM1_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM2)
    {
        TIM2_Manage_Object.TIM_Handler = htim;
        TIM2_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM3)
    {
        TIM3_Manage_Object.TIM_Handler = htim;
        TIM3_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM4)
    {
        TIM4_Manage_Object.TIM_Handler = htim;
        TIM4_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM5)
    {
        TIM5_Manage_Object.TIM_Handler = htim;
        TIM5_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM6)
    {
        TIM6_Manage_Object.TIM_Handler = htim;
        TIM6_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM7)
    {
        TIM7_Manage_Object.TIM_Handler = htim;
        TIM7_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM8)
    {
        TIM8_Manage_Object.TIM_Handler = htim;
        TIM8_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM9)
    {
        TIM9_Manage_Object.TIM_Handler = htim;
        TIM9_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM10)
    {
        TIM10_Manage_Object.TIM_Handler = htim;
        TIM10_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM11)
    {
        TIM11_Manage_Object.TIM_Handler = htim;
        TIM11_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM12)
    {
        TIM12_Manage_Object.TIM_Handler = htim;
        TIM12_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM13)
    {
        TIM13_Manage_Object.TIM_Handler = htim;
        TIM13_Manage_Object.Callback_Function = Callback_Function;
    }
    else if (htim->Instance == TIM14)
    {
        TIM14_Manage_Object.TIM_Handler = htim;
        TIM14_Manage_Object.Callback_Function = Callback_Function;
    }
}

/**
 * @brief HAL库TIM定时器中断
 *
 * @param htim TIM编号
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    // 选择回调函数
    if (htim->Instance == TIM1)
    {
        if(TIM1_Manage_Object.Callback_Function != NULL)
        {
            TIM1_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM2)
    {
        if(TIM2_Manage_Object.Callback_Function != NULL)
        {
            TIM2_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM3)
    {
        if(TIM3_Manage_Object.Callback_Function != NULL)
        {
            TIM3_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM4)
    {
        if(TIM4_Manage_Object.Callback_Function != NULL)
        {
            TIM4_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM5)
    {
        if(TIM5_Manage_Object.Callback_Function != NULL)
        {
            TIM5_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM6)
    {
        if(TIM6_Manage_Object.Callback_Function != NULL)
        {
            TIM6_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM7)
    {
        if(TIM7_Manage_Object.Callback_Function != NULL)
        {
            TIM7_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM8)
    {
        if(TIM8_Manage_Object.Callback_Function != NULL)
        {
            TIM8_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM9)
    {
        if(TIM9_Manage_Object.Callback_Function != NULL)
        {
            TIM9_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM10)
    {
        if(TIM10_Manage_Object.Callback_Function != NULL)
        {
            TIM10_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM11)
    {
        if(TIM11_Manage_Object.Callback_Function != NULL)
        {
            TIM11_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM12)
    {
        if(TIM12_Manage_Object.Callback_Function != NULL)
        {
            TIM12_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM13)
    {
        if(TIM13_Manage_Object.Callback_Function != NULL)
        {
            TIM13_Manage_Object.Callback_Function();
        }
    }
    else if (htim->Instance == TIM14)
    {
        if(TIM14_Manage_Object.Callback_Function != NULL)
        {
            TIM14_Manage_Object.Callback_Function();
        }
    }
}