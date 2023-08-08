#ifndef __KEY_H
#define __KEY_H


// Start "Study Mode", but need another key input to specify the function number need to be modified subsequently
#define START_STUDYING_KEY 64   

// During "Action Mode", if the user realize the input is wrong, pressing this key restarts the recording    
#define RESET_RECORDING_KEY 63      

// Start "Action Mode" with an n seconds wait time subsequently
#define START_RECORDING_KEY 62         

// There is no key event
#define NO_EVENT_KEY 0



void Key_Init(void);
uint16_t Key_GetNum(void);

#endif
