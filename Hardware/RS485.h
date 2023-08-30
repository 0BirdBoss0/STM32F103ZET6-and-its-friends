#ifndef _RS485_H
#define _RS485_H

#include "system.h"
#include "adc.h"

extern u8 USART2_RX_BUF[64]; // ���ջ��棬���64�ֽ�
extern u8 USART2_RX_CNT;
extern u32 regGroup[40]; // Modbus�Ĵ����飬��ַΪ0x00~0x04
extern u16 dizhi;
extern u16 btl[5];
extern u16 bt;
extern u16 bt_last;          // ģʽ����
#define RS485_TX_EN PGout(3) // 485ģʽ����.0,����;1,����.

void RS485_Init(u32 bound);
void TIM2_Init(void);
void UartRxMonitor(u8 ms);               // ���ڽ��ռ��
void UartDriver(void);                   // ������������void UartRead(u8 *buf, u8 len); //���ڽ�������
void rs485_UartWrite(u8 *buf2, u8 len2); // ���ڷ�������
u8 UartRead(u8 *buf, u8 len);

#endif
