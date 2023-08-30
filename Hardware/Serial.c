#include "stm32f10x.h" // Device header
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStrue;
    USART_InitTypeDef USART_InitStrue;
    NVIC_InitTypeDef NVIC_InitStrue;

    // 外设使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    USART_DeInit(USART2); // 复位串口2 -> 可以没有

    // 初始化 串口对应IO口  TX-PA2  RX-PA3
    GPIO_InitStrue.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStrue.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStrue);

    GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStrue);

    // 初始化 串口模式状态
    USART_InitStrue.USART_BaudRate            = 9600;                           // 波特率
    USART_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制
    USART_InitStrue.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  // 发送 接收 模式都使用
    USART_InitStrue.USART_Parity              = USART_Parity_No;                // 没有奇偶校验
    USART_InitStrue.USART_StopBits            = USART_StopBits_1;               // 一位停止位
    USART_InitStrue.USART_WordLength          = USART_WordLength_8b;            // 每次发送数据宽度为8位
    USART_Init(USART2, &USART_InitStrue);

    USART_Cmd(USART2, ENABLE);                     // 使能串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // 开启接收中断

    // 初始化 中断优先级
    NVIC_InitStrue.NVIC_IRQChannel                   = USART2_IRQn;
    NVIC_InitStrue.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStrue.NVIC_IRQChannelSubPriority        = 1;
}

void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART2, Byte);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        ;
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(Array[i]);
    }
}

void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++) {
        Serial_SendByte(String[i]);
    }
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--) {
        Result *= X;
    }
    return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

void Serial_Printf(char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

void USART2_IRQHandler(void) // 串口2中断服务函数
{
    u8 res;
    if (USART_GetITStatus(USART2, USART_IT_RXNE)) // 中断标志
    {
        res = USART_ReceiveData(USART2); // 串口2 接收
        USART_SendData(USART2, res);     // 串口2 发送
    }
}
