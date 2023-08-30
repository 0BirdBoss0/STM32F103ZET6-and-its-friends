#ifndef __KEY_H
#define __KEY_H

/************************
R1----------------->  PD0
R2----------------->  PD1
R3----------------->  PD2
R4----------------->  PD3
R5----------------->  PD4
R6----------------->  PD5
R7----------------->  PD6
R8----------------->  PD7
C1----------------->  PD8
C2----------------->  PD9
C3----------------->  PD10
C4----------------->  PD11
C5----------------->  PD12
C6----------------->  PD13
C7----------------->  PD14
C8----------------->  PD15
**************************/

  

// Start "Action Mode" with an n seconds wait time subsequently
#define RESET_RECORDING_KEY 61         

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
