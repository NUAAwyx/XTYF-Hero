#include "dvc_vofa.h"

float vofa_cmd_data;
enum Enum_VOFA_cmd vofa_cmd_type;

uint8_t _send_data[400];
float test_data[40];

void vofa_Init(UART_HandleTypeDef *huart, UART_Call_Back Callback_Function, uint16_t Rx_Buffer_Length)
{
    if (huart->Instance == USART6)
    {
        UART_Init(huart, Callback_Function, Rx_Buffer_Length);
    }
}

void vofa_send(float *data, uint8_t num)
{
    for(int i = 0; i < num; i++)
    {
        for(int j = 4 * i; j < 4 * i + 4; j++)
        {
            _send_data[j] = ((uint8_t*)data)[j];
        }
    }
    _send_data[4 * num] = 0x00;
    _send_data[4 * num + 1] = 0x00;
    _send_data[4 * num + 2] = 0x80;
    _send_data[4 * num + 3] = 0x7f;
    HAL_UART_Transmit_DMA(&huart6, _send_data, 4 * num + 4);
    //HAL_UART_Transmit(&huart6, _send_data, 4 * num + 4, HAL_MAX_DELAY);
}

void vofa_data_process(uint8_t* data) 
{
    // 假设 data 是一个以空字符结尾的字符串
    char *str = (char*)data;
    char *endptr;

    // 跳过非数字字符，找到 '=' 后的部分
    while (*str && *str != '=') {
        str++;
    }

    // 如果找到了 '='，则跳过它
    if (*str == '=') {
        str++;
    }

    // 将字符串转换为浮点数
    vofa_cmd_data = strtof(str, &endptr);
}

void vofa_cmd_type_process(uint8_t* data)
{
    switch (data[0])
    {
    case 'O':
        switch (data[1])
        {
        case 'P':
            vofa_cmd_type = OP;
            break;
        case 'I':
            vofa_cmd_type = OI;
            break;
        case 'D':
            vofa_cmd_type = OD;
            break;
        case 'F':
            vofa_cmd_type = OF;
            break;
        case 'T':
            vofa_cmd_type = OT;
            break;
        default:
            break;
        }
        break;
    
    case 'A':
        switch (data[1])
        {
        case 'P':
            vofa_cmd_type = AP;
            break;
        case 'I':
            vofa_cmd_type = AI;
            break;
        case 'D':
            vofa_cmd_type = AD;
            break;
        case 'F':
            vofa_cmd_type = AF;
            break;
        case 'T':
            vofa_cmd_type = AT;
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

void vofa_callback(uint8_t *Buffer, uint16_t Length)
{
    vofa_cmd_type_process(Buffer);
    vofa_data_process(Buffer);
}

