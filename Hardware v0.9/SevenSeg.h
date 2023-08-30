#ifndef __SEVENSEG_H
#define __SEVENSEG_H

/************************
VCC-------------------------->  供电
DIO(SDI)(DS)----------------->  PC3 (PA0)
RCLK(LOAD)(ST_CP)------------>  PC1 (PC2)
SCLK(SHCP-------------------->  PC2 (PC1)
GND-------------------------->  接地
**************************/

void HC595_GPIO_Configuration(void);
//void HC595_Send_Data(unsigned char num, unsigned char show_bit);
void HC595_Send_Byte(unsigned char byte);
void display(unsigned int n);


#endif
