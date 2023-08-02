#ifndef __SEVENSEG_H
#define __SEVENSEG_H

void HC595_GPIO_Configuration(void);
//void HC595_Send_Data(unsigned char num, unsigned char show_bit);
void HC595_Send_Byte(unsigned char byte);
void display(unsigned int n);


#endif
