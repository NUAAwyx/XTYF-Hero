#ifndef BMI088MIDDLEWARE_H
#define BMI088MIDDLEWARE_H

#include "spi.h"
#include "dma.h"


#define CS1_Accel_Pin GPIO_PIN_4
#define CS1_Accel_GPIO_Port GPIOA

#define CS1_Gyro_Pin GPIO_PIN_0
#define CS1_Gyro_GPIO_Port GPIOB

#define INT1_Accel_Pin GPIO_PIN_4
#define INT1_Accel_GPIO_Port GPIOC

#define INT1_Gyro_Pin GPIO_PIN_5
#define INT1_Gyro_GPIO_Port GPIOC

void BMI088_GPIO_init(void);
void BMI088_com_init(void);
void BMI088_delay_ms(uint16_t ms);
void BMI088_delay_us(uint16_t us);

void BMI088_ACCEL_NS_L(void);
void BMI088_ACCEL_NS_H(void);

void BMI088_GYRO_NS_L(void);
void BMI088_GYRO_NS_H(void);

uint8_t BMI088_read_write_byte(uint8_t reg);


#endif
