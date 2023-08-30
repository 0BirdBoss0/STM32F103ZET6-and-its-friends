#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_0);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	GPIO_SetBits(GPIOE, GPIO_Pin_2);
	GPIO_SetBits(GPIOE, GPIO_Pin_3);
	GPIO_SetBits(GPIOE, GPIO_Pin_4);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	GPIO_SetBits(GPIOE, GPIO_Pin_6);
	GPIO_SetBits(GPIOE, GPIO_Pin_7);
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
	if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8) == 0)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOE, GPIO_Pin_8);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_9);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_9);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_9) == 0)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_9);
	}
	else
	{
		GPIO_ResetBits(GPIOE, GPIO_Pin_9);
	}
}

void LED3_ON(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

void LED3_OFF(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_10);
}

void LED3_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_10) == 0)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_10);
	}
	else
	{
		GPIO_ResetBits(GPIOE, GPIO_Pin_10);
	}
}
