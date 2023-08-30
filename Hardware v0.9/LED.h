#ifndef __LED_H
#define __LED_H

/************************
LED0----------------->  PE0 (PB9)
LED1----------------->  PE1 (PE2)
LED2----------------->  PE2 (PE1)
LED3----------------->  PE3 (PE4)
LED4----------------->  PE4 (PE3)
LED5----------------->  PE5 (PE6)
LED6----------------->  PE6 (PE5)
LED7----------------->  PE7 (PG1)
LED8----------------->  PE8 (PE9)
LED9----------------->  PE9 (PE8)
LED10---------------->  PE10(PE11)
LED11---------------->  PE11(PE10)
LED12---------------->  PE12(PE13)
LED13---------------->  PE13(PE12)
LED14---------------->  PE14(PE15)
LED15---------------->  PE15(PE14)
**************************/

void LED_Init(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED1_Turn(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_Turn(void);
void LED3_ON(void);
void LED3_OFF(void);
void LED3_Turn(void);

#endif
