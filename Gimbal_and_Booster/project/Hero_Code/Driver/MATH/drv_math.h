#ifndef __DRV_MATH_H
#define __DRV_MATH_H

#include "arm_math.h"

// rpm换算到rad/s
#define RPM_TO_RADPS (2.0f * PI / 60.0f)
// deg换算到rad
#define DEG_TO_RAD (PI / 180.0f)
// 摄氏度换算到开氏度
#define CELSIUS_TO_KELVIN (273.15f)

// 归一化
float Math_Modulus_Normalization(float x, float modulus);

// 16位大小端转换
void Math_Endian_Reverse_16_Single(void *Address);

// 16位大小端转换
uint16_t Math_Endian_Reverse_16(void *Source, void *Destination);

// 32位大小端转换
void Math_Endian_Reverse_32_Single(void *Address);

// 32位大小端转换
uint32_t Math_Endian_Reverse_32_Double(void *Source, void *Destination);

// 求和
uint8_t Math_Sum_8(uint8_t *Address, uint32_t Length);

// 求和
uint16_t Math_Sum_16(uint16_t *Address, uint32_t Length);

// 求和
uint32_t Math_Sum_32(uint32_t *Address, uint32_t Length);

// 将浮点数映射到整型
int32_t Math_Float_To_Int(float x, float Float_Min, float Float_Max, int32_t Int_Min, int32_t Int_Max);

// 将整型映射到浮点数
float Math_Int_To_Float(int32_t x, int32_t Int_Min, int32_t Int_Max, float Float_Min, float Float_Max);

// 限幅函数
float Math_Constrain(float *x, float Min, float Max);

// 求绝对值
float Math_Abs(float x);





#endif