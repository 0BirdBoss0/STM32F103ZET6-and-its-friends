#ifndef __KEY_H
#define __KEY_H

/************************
R1----------------->  PD1
R2----------------->  PD0
R3----------------->  PD3
R4----------------->  PD2
R5----------------->  PD5
R6----------------->  PD4
R7----------------->  PD7
R8----------------->  PD6
C1----------------->  PD9
C2----------------->  PD8
C3----------------->  PD11
C4----------------->  PD10
C5----------------->  PD13
C6----------------->  PD12
C7----------------->  PD15
C8----------------->  PD14
**************************/

// Add 1 second to the first turn of the waiting.
#define FIRST_TIMER_INCREMENT_KEY 57

// Add 1 second to the second turn of the waiting.
#define SECOND_TIMER_INCREMENT_KEY 58

// Add 1 second to the thrid turn of the waiting.
#define THIRD_TIMER_INCREMENT_KEY 59

// Add 1 second to the fourth turn of the waiting.
#define FOURTH_TIMER_INCREMENT_KEY 60

// Add 1 second to the fifth turn of the waiting.
#define FIFTH_TIMER_INCREMENT_KEY 61

// Start "Study Mode", but need another key input to specify the function number need to be modified subsequently
#define START_STUDYING_KEY 62

// During "Normal Mode", if the user realize the input is wrong, pressing this key restarts the recording
#define START_NORMAL_KEY 63

// Start "Action Mode" with an n seconds wait time subsequently
#define END_KEY 64

// There is no key event
#define NO_EVENT_KEY 0

void Key_Init(void);
uint16_t Key_GetNum(void);

#endif
