#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;

	// colume
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// row
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);


}

uint8_t Key_GetNum(void)
{
	uint16_t KeyNum = 0;
	uint16_t temp=0;

	// if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0)
	// {
	// 	Delay_ms(20);
	// 	while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0);
	// 	Delay_ms(20);
	// 	KeyNum = 1;
	// }
	// if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0)
	// {
	// 	Delay_ms(20);
	// 	while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0);
	// 	Delay_ms(20);
	// 	KeyNum = 2;
	// }

	/*************Scan  1st  Line************************/
	// GPIOD->ODR=0X00;
	// GPIO_Write(GPIOD,0x00FE); // pull down R1(A0)
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	GPIO_SetBits(GPIOD, GPIO_Pin_1);
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	GPIO_SetBits(GPIOD, GPIO_Pin_3);
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
	GPIO_SetBits(GPIOD, GPIO_Pin_5);
	GPIO_SetBits(GPIOD, GPIO_Pin_6);
	GPIO_SetBits(GPIOD, GPIO_Pin_7);

	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XFE);
			switch (temp)
			{
			// the first key in this row is pressed, 
			// temp here should be 0b 1111 1110 1111 1110,
			// since we set R1(A0) to 0, pressing sw1 will make C1(B8) to be 0
			case 0xFEFE: KeyNum = 1; break;  // 1111 1110
			// the second key in this row is pressed.
			case 0xFDFE: KeyNum = 2; break;  // 1111 1101
			case 0xFBFE: KeyNum = 3; break;  // 1111 1011
			case 0xF7FE: KeyNum = 4; break;  // 1111 0111

			case 0xEFFE: KeyNum = 5; break;  // 1110 1111
			case 0xDFFE: KeyNum = 6; break;  // 1101 1111
			case 0xBFFE: KeyNum = 7; break;  // 1011 1111
			case 0x7FFE: KeyNum = 8; break;  // 0111 1111

			// ********************************
			// two keys in this row are pressed at the same time
			// case 0xFCFE: KeyNum = 101; break;	// 1111 1100
			// case 0xFAFE: KeyNum = 102; break;	// 1111 1010
			// case 0xF6FE: KeyNum = 103; break;	// 1111 0110
			// case 0xEEFE: KeyNum = 104; break;	// 1110 1110
			// case 0xDEFE: KeyNum = 105; break;	// 1101 1110
			// case 0xBEFE: KeyNum = 106; break;	// 1011 1110
			// case 0x7EFE: KeyNum = 107; break;	// 0111 1110

			// case 0xF9FE: KeyNum = 108; break;	// 1111 1001
			// case 0xF5FE: KeyNum = 109; break;	// 1111 0101
			// case 0xEDFE: KeyNum = 110; break;	// 1110 1101
			// case 0xDDFE: KeyNum = 111; break;	// 1101 1101
			// case 0xBDFE: KeyNum = 112; break;	// 1011 1101
			// case 0x7DFE: KeyNum = 113; break;	// 0111 1101

			// case 0xF3FE: KeyNum = 114; break;	// 1111 0011
			// case 0xEBFE: KeyNum = 115; break;	// 1110 1011
			// case 0xDBFE: KeyNum = 116; break;	// 1101 1011
			// case 0xBBFE: KeyNum = 117; break;	// 1011 1011
			// case 0x7BFE: KeyNum = 118; break;	// 0111 1011

			// case 0xE7FE: KeyNum = 119; break;	// 1110 0111
			// case 0xD7FE: KeyNum = 120; break;	// 1101 0111
			// case 0xB7FE: KeyNum = 121; break;	// 1011 0111
			// case 0x77FE: KeyNum = 122; break;	// 0111 0111

			// case 0xCFFE: KeyNum = 123; break;	// 1100 1111
			// case 0xAFFE: KeyNum = 124; break;	// 1010 1111
			// case 0x6FFE: KeyNum = 125; break;	// 0110 1111

			// case 0x9FFE: KeyNum = 126; break;	// 1010 1111
			// case 0x5FFE: KeyNum = 127; break;	// 0110 1111

			// case 0x3FFE: KeyNum = 128; break;	// 1010 1111

			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  2nd  Line************************/
	// GPIOD->ODR=0X00;
	// GPIO_Write(GPIOD,0x00FD); // pull down R2(A1)
	GPIO_SetBits(GPIOD, GPIO_Pin_0);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XFD);
			switch (temp)
			{
			case 0xFEFD: KeyNum = 9; break;
			case 0xFDFD: KeyNum = 10; break;
			case 0xFBFD: KeyNum = 11; break;
			case 0xF7FD: KeyNum = 12; break;

			case 0xEFFD: KeyNum = 13; break;
			case 0xDFFD: KeyNum = 14; break;
			case 0xBFFD: KeyNum = 15; break;
			case 0x7FFD: KeyNum = 16; break;

			// ********************************
			// two keys in this row are pressed at the same time
			case 0xFCFD: KeyNum = 101; break;	// 1111 1100
			case 0xFAFD: KeyNum = 102; break;	// 1111 1010
			case 0xF6FD: KeyNum = 103; break;	// 1111 0110
			case 0xEEFD: KeyNum = 104; break;	// 1110 1110
			case 0xDEFD: KeyNum = 105; break;	// 1101 1110
			case 0xBEFD: KeyNum = 106; break;	// 1011 1110
			case 0x7EFD: KeyNum = 107; break;	// 0111 1110

			case 0xF9FD: KeyNum = 108; break;	// 1111 1001
			case 0xF5FD: KeyNum = 109; break;	// 1111 0101
			case 0xEDFD: KeyNum = 110; break;	// 1110 1101
			case 0xDDFD: KeyNum = 111; break;	// 1101 1101
			case 0xBDFD: KeyNum = 112; break;	// 1011 1101
			case 0x7DFD: KeyNum = 113; break;	// 0111 1101

			case 0xF3FD: KeyNum = 114; break;	// 1111 0011
			case 0xEBFD: KeyNum = 115; break;	// 1110 1011
			case 0xDBFD: KeyNum = 116; break;	// 1101 1011
			case 0xBBFD: KeyNum = 117; break;	// 1011 1011
			case 0x7BFD: KeyNum = 118; break;	// 0111 1011

			case 0xE7FD: KeyNum = 119; break;	// 1110 0111
			case 0xD7FD: KeyNum = 120; break;	// 1101 0111
			case 0xB7FD: KeyNum = 121; break;	// 1011 0111
			case 0x77FD: KeyNum = 122; break;	// 0111 0111
			
			case 0xCFFD: KeyNum = 123; break;	// 1100 1111
			case 0xAFFD: KeyNum = 124; break;	// 1010 1111
			case 0x6FFD: KeyNum = 125; break;	// 0110 1111

			case 0x9FFD: KeyNum = 126; break;	// 1010 1111
			case 0x5FFD: KeyNum = 127; break;	// 0110 1111

			case 0x3FFD: KeyNum = 128; break;	// 1010 1111
			default: KeyNum = 0; break;
			}
		}
	}



	/*************Scan  3rd  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_1);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // pull down R3(A2)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XFB);
			switch (temp)
			{
			case 0xFEFB: KeyNum = 17; break;
			case 0xFDFB: KeyNum = 18; break;
			case 0xFBFB: KeyNum = 19; break;
			case 0xF7FB: KeyNum = 20; break;

			case 0xEFFB: KeyNum = 21; break;
			case 0xDFFB: KeyNum = 22; break;
			case 0xBFFB: KeyNum = 23; break;
			case 0x7FFB: KeyNum = 24; break;
			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  4th  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	GPIO_ResetBits(GPIOD, GPIO_Pin_3); // pull down R4(A3)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XF7);
			switch (temp)
			{
			case 0xFEF7: KeyNum = 25; break;
			case 0xFDF7: KeyNum = 26; break;
			case 0xFBF7: KeyNum = 27; break;
			case 0xF7F7: KeyNum = 28; break;

			case 0xEFF7: KeyNum = 29; break;
			case 0xDFF7: KeyNum = 30; break;
			case 0xBFF7: KeyNum = 31; break;
			case 0x7FF7: KeyNum = 32; break;
			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  5th  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_3);
	GPIO_ResetBits(GPIOD, GPIO_Pin_4); // pull down R5(A4)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XEF);
			switch (temp)
			{
			case 0xFEEF: KeyNum = 33; break;
			case 0xFDEF: KeyNum = 34; break;
			case 0xFBEF: KeyNum = 35; break;
			case 0xF7EF: KeyNum = 36; break;

			case 0xEFEF: KeyNum = 37; break;
			case 0xDFEF: KeyNum = 38; break;
			case 0xBFEF: KeyNum = 39; break;
			case 0x7FEF: KeyNum = 40; break;
			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  6th  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
	GPIO_ResetBits(GPIOD, GPIO_Pin_5); // pull down R6(A5)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XDF);
			switch (temp)
			{
			case 0xFEDF: KeyNum = 41; break;
			case 0xFDDF: KeyNum = 42; break;
			case 0xFBDF: KeyNum = 43; break;
			case 0xF7DF: KeyNum = 44; break;

			case 0xEFDF: KeyNum = 45; break;
			case 0xDFDF: KeyNum = 46; break;
			case 0xBFDF: KeyNum = 47; break;
			case 0x7FDF: KeyNum = 48; break;
			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  7th  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_5);
	GPIO_ResetBits(GPIOD, GPIO_Pin_6); // pull down R7(A6)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0XBF);
			switch (temp)
			{
			case 0xFEBF: KeyNum = 49; break;
			case 0xFDBF: KeyNum = 50; break;
			case 0xFBBF: KeyNum = 51; break;
			case 0xF7BF: KeyNum = 52; break;

			case 0xEFBF: KeyNum = 53; break;
			case 0xDFBF: KeyNum = 54; break;
			case 0xBFBF: KeyNum = 55; break;
			case 0x7FBF: KeyNum = 56; break;
			default: KeyNum = 0; break;
			}
		}
	}




	/*************Scan  8th  Line************************/
	// GPIOD->ODR=0X00;
	GPIO_SetBits(GPIOD, GPIO_Pin_6);
	GPIO_ResetBits(GPIOD, GPIO_Pin_7); // pull down R8(A7)
	if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
		Delay_ms(15);
		if(((GPIOD->IDR >> 8) & 0XFF) != 0XFF){
			temp=(((GPIOD->IDR >> 8) << 8) + 0X7F);
			switch (temp)
			{
			case 0xFE7F: KeyNum = 57; break;
			case 0xFD7F: KeyNum = 58; break;
			case 0xFB7F: KeyNum = 59; break;
			case 0xF77F: KeyNum = 60; break;

			case 0xEF7F: KeyNum = 61; break;
			case 0xDF7F: KeyNum = 62; break;
			case 0xBF7F: KeyNum = 63; break;
			case 0x7F7F: KeyNum = 64; break;
			default: KeyNum = 0; break;
			}
		}
	}
	return KeyNum;
}
