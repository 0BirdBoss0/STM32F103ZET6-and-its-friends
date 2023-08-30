#ifndef _control_H
#define _control_H
//#include "adc.h"
#include "rs485.h"
#include "stm32_flash.h"
#include "rtc.h" 
#include "time.h"
#include "system.h"
#include "SysTick.h"
#include "key.h"
//#include "tftlcd.h"
#include "led.h"
//#include "beep.h"
#include "stdio.h"
#include "LCD.h"
void Page_control(void);
void Screen_interface(void);
//void Eight_Input(void);
void Led_Instructions(void);
void Lcd1_display(void);
void Lcd2_display(void);
void Lcd3_display(void);
void Lcd4_display(void);
void Lcd5_display(void);
void flash_modbus(void);
#define STM32_FLASH_SAVE_ADDR    0X08070000
#define STM32_FLASH_SAVE_ADDR1  (0X08070000+4)
#define STM32_FLASH_SAVE_ADDR2  (0X08070000+8)
#define STM32_FLASH_SAVE_ADDR3  (0X08070000+12)
#define STM32_FLASH_SAVE_ADDR4  (0X08070000+16)
#define STM32_FLASH_SAVE_ADDR5  (0X08070000+20)
#define STM32_FLASH_SAVE_ADDR6  (0X08070000+24)
#define STM32_FLASH_SAVE_ADDR7  (0X08070000+28)
#define STM32_FLASH_SAVE_ADDR8  (0X08070000+32)
#define TEXTLEN sizeof(text_buf)
extern u8 Page_number;//页码设置
extern u8 Flag;
extern u16 color;
extern u16 V_max,I_max;

extern u16 Voverload,Ioverload;//电压电流超载指示
extern u16 Closing,Opening;
extern u16 Remote_operation,Local_operation;
extern u16 Energystorage_state;
extern u16 Opening_control,Closing_control;//分合闸控制
extern u8 Flag2;



#endif










