#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/************************
VCC------------>供电
DIO(SDI)------------>PB15   (PG7)
RCLK(LOAD)------------>PB12 (PG5)
SCLK------------>PB13       (PG6)
GND------------>接地
**************************/

unsigned int num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff, 0x00};
//创建一个数组，0-9所对应的十六进制数

void HC595_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
	GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET);
}

/*********************************
参数：byte 所传入的数据，
  			是要显示的数字或者是对应显示的位数
**********************************/
/************************
VCC------------>供电
DIO------------>PB15
RCLK------------>PB12  
SCLK------------>PB13  
GND------------>接地
**************************/
//串入
void HC595_Send_Byte(unsigned char byte)
{
	unsigned int i;
	
	for(i = 0; i < 8; i++)
	{
		if(byte & 0x80)
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_SET);
		else
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET);
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
		Delay_us(10);
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
		Delay_us(10);
		
		byte <<= 1;
	}
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
	Delay_us(10);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
	Delay_us(10);
}





void display(unsigned int n)
{
	static unsigned int hundred_bit, ten_bit, single_bit;
	

	hundred_bit = (n % 1000) / 100;
	ten_bit = n % 1000 % 100 / 10;
	single_bit = n % 10;
	HC595_Send_Byte(num[single_bit]);
	HC595_Send_Byte(num[ten_bit]);
	HC595_Send_Byte(num[hundred_bit]);
	
	


}


