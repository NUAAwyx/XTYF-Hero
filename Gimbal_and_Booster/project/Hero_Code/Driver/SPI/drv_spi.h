#ifndef DRV_SPI_H
#define DRV_SPI_H

/* Includes ------------------------------------------------------------------*/

#include "spi.h"
#include "string.h"

/* Exported macros -----------------------------------------------------------*/

// 缓冲区字节长度
#define SPI_BUFFER_SIZE 256

/* Exported types ------------------------------------------------------------*/

/**
 * @brief SPI通信接收回调函数数据类型
 *
 */
typedef void (*SPI_Call_Back)(uint8_t *Tx_Buffer, uint8_t *Rx_Buffer, uint16_t Length);

/**
 * @brief SPI通信处理结构体
 *
 */
struct Struct_SPI_Manage_Object
{
    SPI_HandleTypeDef *SPI_Handler;
    GPIO_TypeDef *Now_GPIOx;
    uint16_t Now_GPIO_Pin;
    uint8_t Tx_Buffer[SPI_BUFFER_SIZE];
    uint8_t Rx_Buffer[SPI_BUFFER_SIZE];
    uint16_t Now_Tx_Length;
    uint16_t Now_Rx_Length;
    SPI_Call_Back Callback_Function;
};

/* Exported variables ---------------------------------------------------------*/

extern struct Struct_SPI_Manage_Object SPI1_Manage_Object;
extern struct Struct_SPI_Manage_Object SPI2_Manage_Object;
extern struct Struct_SPI_Manage_Object SPI3_Manage_Object;


/* Exported function declarations ---------------------------------------------*/

void SPI_Init(SPI_HandleTypeDef *hspi, SPI_Call_Back Callback_Function);

uint8_t SPI_Send_Receive_Data(SPI_HandleTypeDef *hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t Tx_Length, uint16_t Rx_Length);

void TIM_100us_SPI_PeriodElapsedCallback();

#endif