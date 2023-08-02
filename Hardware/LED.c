#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
	GPIO_SetBits(GPIOF, GPIO_Pin_9);
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_8) == 0)
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_8);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_9);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_9);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_9) == 0)
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_9);
	}
	else
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
	}
}

void LED3_ON(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_10);
}

void LED3_OFF(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
}

void LED3_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_10) == 0)
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
	}
	else
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
	}
}
