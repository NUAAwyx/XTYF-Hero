#include "drv_math.h"

float Math_Modulus_Normalization(float x, float modulus)
{
    float tmp;

    tmp = fmod(x + modulus / 2.0f, modulus);

    if (tmp < 0.0f)
    {
        tmp += modulus;
    }

    return (tmp - modulus / 2.0f);
}


/**
 * @brief 16位大小端转换
 *
 * @param Address 地址
 */
void Math_Endian_Reverse_16_Single(void *Address)
{
    uint8_t *temp_address_8 = (uint8_t *) Address;
    uint16_t *temp_address_16 = (uint16_t *) Address;
    *temp_address_16 = temp_address_8[0] << 8 | temp_address_8[1];
}

/**
 * @brief 16位大小端转换
 *
 * @param Source 源数据地址
 * @param Destination 目标存储地址
 * @return uint16_t 结果
 */
uint16_t Math_Endian_Reverse_16(void *Source, void *Destination)
{
    uint8_t *temp_address_8 = (uint8_t *) Source;
    uint16_t temp_address_16;
    temp_address_16 = temp_address_8[0] << 8 | temp_address_8[1];

    if (Destination != NULL)
    {
        uint8_t *temp_source, *temp_destination;
        temp_source = (uint8_t *) Source;
        temp_destination = (uint8_t *) Destination;

        temp_destination[0] = temp_source[1];
        temp_destination[1] = temp_source[0];
    }

    return temp_address_16;
}

/**
 * @brief 32位大小端转换
 *
 * @param Address 地址
 */
void Math_Endian_Reverse_32_Single(void *Address)
{
    uint8_t *temp_address_8 = (uint8_t *) Address;
    uint32_t *temp_address_32 = (uint32_t *) Address;
    *temp_address_32 = temp_address_8[0] << 24 | temp_address_8[1] << 16 | temp_address_8[2] << 8 | temp_address_8[3];
}

/**
 * @brief 32位大小端转换
 *
 * @param Source 源数据地址
 * @param Destination 目标存储地址
 * @return uint32_t 结果
 */
uint32_t Math_Endian_Reverse_32_Double(void *Source, void *Destination)
{
    uint8_t *temp_address_8 = (uint8_t *) Source;
    uint32_t temp_address_32;
    temp_address_32 = temp_address_8[0] << 24 | temp_address_8[1] << 16 | temp_address_8[2] << 8 | temp_address_8[3];

    if (Destination != NULL)
    {
        uint8_t *temp_source, *temp_destination;
        temp_source = (uint8_t *) Source;
        temp_destination = (uint8_t *) Destination;

        temp_destination[0] = temp_source[3];
        temp_destination[1] = temp_source[2];
        temp_destination[2] = temp_source[1];
        temp_destination[3] = temp_source[0];
    }

    return temp_address_32;
}

/**
 * @brief 求和
 *
 * @param Address 起始地址
 * @param Length 被加的数据的数量, 注意不是字节数
 * @return uint8_t 结果
 */
uint8_t Math_Sum_8(uint8_t *Address, uint32_t Length)
{
    uint8_t sum = 0;
    for (int i = 0; i < Length; i++)
    {
        sum += Address[i];
    }
    return (sum);
}

/**
 * @brief 求和
 *
 * @param Address 起始地址
 * @param Length 被加的数据的数量, 注意不是字节数
 * @return uint16_t 结果
 */
uint16_t Math_Sum_16(uint16_t *Address, uint32_t Length)
{
    uint16_t sum = 0;
    for (int i = 0; i < Length; i++)
    {
        sum += Address[i];
    }
    return (sum);
}

/**
 * @brief 求和
 *
 * @param Address 起始地址
 * @param Length 被加的数据的数量, 注意不是字节数
 * @return uint32_t 结果
 */
uint32_t Math_Sum_32(uint32_t *Address, uint32_t Length)
{
    uint32_t sum = 0;
    for (int i = 0; i < Length; i++)
    {
        sum += Address[i];
    }
    return (sum);
}

/**
 * @brief 将浮点数映射到整型
 *
 * @param x 浮点数
 * @param Float_Min 浮点数最小值
 * @param Float_Max 浮点数最大值
 * @param Int_Min 整型最小值
 * @param Int_Max 整型最大值
 * @return int32_t 整型
 */
int32_t Math_Float_To_Int(float x, float Float_Min, float Float_Max, int32_t Int_Min, int32_t Int_Max)
{
    float tmp = (x - Float_Min) / (Float_Max - Float_Min);
    int32_t out = tmp * (float) (Int_Max - Int_Min) + Int_Min;
    return (out);
}

/**
 * @brief 将整型映射到浮点数
 *
 * @param x 整型
 * @param Int_Min 整型最小值
 * @param Int_Max 整型最大值
 * @param Float_Min 浮点数最小值
 * @param Float_Max 浮点数最大值
 * @return float 浮点数
 */
float Math_Int_To_Float(int32_t x, int32_t Int_Min, int32_t Int_Max, float Float_Min, float Float_Max)
{
    float tmp = (float) (x - Int_Min) / (float) (Int_Max - Int_Min);
    float out = tmp * (Float_Max - Float_Min) + Float_Min;
    return (out);
}

/**
 * @brief 限幅函数
 *
 * @param x 传入数据
 * @param Min 最小值
 * @param Max 最大值
 */
float Math_Constrain(float *x, float Min, float Max)
{
    if (*x < Min)
    {
        *x = Min;
    }
    else if (*x > Max)
    {
        *x = Max;
    }
    return (*x);
}

/**
 * @brief 求绝对值
 *
 * @param x 传入数据
 * @return Type x的绝对值
 */
float Math_Abs(float x)
{
    return ((x > 0) ? x : -x);
}

/**
 * @brief 求取模归化
 *
 * @tparam Type 类型
 * @param x 传入数据
 * @param modulus 模数
 * @return Type 返回的归化数, 介于 ±modulus / 2 之间
 */
/* float Math_Modulus_Normalization(float x, float modulus)
{
    float tmp;

    tmp = fmod(x + modulus / 2.0f, modulus);

    if (tmp < 0.0f)
    {
        tmp += modulus;
    }

    return (tmp - modulus / 2.0f);
} */