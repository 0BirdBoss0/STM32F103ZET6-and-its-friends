#include "stm32f10x.h" // Device header
#include "LED2.h"

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_9);
    GPIO_SetBits(GPIOE, GPIO_Pin_1);
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
    GPIO_SetBits(GPIOE, GPIO_Pin_3);
    GPIO_SetBits(GPIOE, GPIO_Pin_4);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_6);
    GPIO_SetBits(GPIOG, GPIO_Pin_1);
    GPIO_SetBits(GPIOE, GPIO_Pin_8);
    GPIO_SetBits(GPIOE, GPIO_Pin_9);
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
    GPIO_SetBits(GPIOE, GPIO_Pin_11);
    GPIO_SetBits(GPIOE, GPIO_Pin_12);
    GPIO_SetBits(GPIOE, GPIO_Pin_13);
    GPIO_SetBits(GPIOE, GPIO_Pin_14);
    GPIO_SetBits(GPIOE, GPIO_Pin_15);
}

void LED1_ON(void)
{
    GPIO_ResetBits(GPIOE, GPIO_Pin_8);
}

void LED1_OFF(void)
{
    GPIO_SetBits(GPIOE, GPIO_Pin_8);
}

void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8) == 0) {
        GPIO_SetBits(GPIOE, GPIO_Pin_8);
    } else {
        GPIO_ResetBits(GPIOE, GPIO_Pin_8);
    }
}

void LED_ON(int light_bit)
{
    (light_bit & 0b0000000000000001) ? GPIO_ResetBits(GPIOB, GPIO_Pin_9) : GPIO_SetBits(GPIOB, GPIO_Pin_9);
    (light_bit & 0b0000000000000010) ? GPIO_ResetBits(GPIOE, GPIO_Pin_2) : GPIO_SetBits(GPIOE, GPIO_Pin_2);
    (light_bit & 0b0000000000000100) ? GPIO_ResetBits(GPIOE, GPIO_Pin_1) : GPIO_SetBits(GPIOE, GPIO_Pin_1);
    (light_bit & 0b0000000000001000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_4) : GPIO_SetBits(GPIOE, GPIO_Pin_4);
    (light_bit & 0b0000000000010000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_3) : GPIO_SetBits(GPIOE, GPIO_Pin_3);
    (light_bit & 0b0000000000100000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_6) : GPIO_SetBits(GPIOE, GPIO_Pin_6);
    (light_bit & 0b0000000001000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_5) : GPIO_SetBits(GPIOE, GPIO_Pin_5);
    (light_bit & 0b0000000010000000) ? GPIO_ResetBits(GPIOG, GPIO_Pin_1) : GPIO_SetBits(GPIOG, GPIO_Pin_1);
    (light_bit & 0b0000000100000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_9) : GPIO_SetBits(GPIOE, GPIO_Pin_9);
    (light_bit & 0b0000001000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_8) : GPIO_SetBits(GPIOE, GPIO_Pin_8);
    (light_bit & 0b0000010000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_11) : GPIO_SetBits(GPIOE, GPIO_Pin_11);
    (light_bit & 0b0000100000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_10) : GPIO_SetBits(GPIOE, GPIO_Pin_10);
    (light_bit & 0b0001000000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_13) : GPIO_SetBits(GPIOE, GPIO_Pin_13);
    (light_bit & 0b0010000000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_12) : GPIO_SetBits(GPIOE, GPIO_Pin_12);
    (light_bit & 0b0100000000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_15) : GPIO_SetBits(GPIOE, GPIO_Pin_15);
    (light_bit & 0b1000000000000000) ? GPIO_ResetBits(GPIOE, GPIO_Pin_14) : GPIO_SetBits(GPIOE, GPIO_Pin_14);
}
