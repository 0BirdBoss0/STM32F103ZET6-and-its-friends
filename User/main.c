#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "Delay.h" 
#include "LED.h"
#include "Key.h"
#include "SevenSeg.h"




uint8_t KeyNum;
uint8_t FunctionNum;
uint8_t KeyNumSelection;
uint8_t KeyArray[3];
uint8_t KeyIndex;
uint8_t PrevKey;
uint8_t KeyData[256][3];



#define START_STUDYING_KEY 64
#define RESET_RECORDING_KEY 63
#define NO_EVENT_KEY 0



int main(void){
	
	LED_Init();


	Key_Init();
	KeyIndex = 0;
	PrevKey = 0;
	KeyNumSelection = 0;
	FunctionNum = 0;
	int study_start = 0;
	int studying_flag = 0;
	memset(KeyData, 0, sizeof(KeyData)); 
	KeyData[1][0] = 1;
	KeyData[1][1] = 2;
	KeyData[1][2] = 3;
	
	
	HC595_GPIO_Configuration();
	display(0);
	

	// while(1){
		
	// 	KeyNum = Key_GetNum();
		

	// 	// when none of the keys are pressed, or when the key is pressed continiously
	// 	// just do nothing
	// 	if ((KeyNum == NO_EVENT_KEY) || (KeyNum == PrevKey)) continue;
			
	// 	display(KeyNum);
	// 	PrevKey = KeyNum;
		

	// 	if ((KeyNum == START_STUDYING_KEY) && (study_start == 0)) {study_start = 1; continue;}
	// 	if (KeyNum == RESET_RECORDING_KEY) {KeyIndex = 0; memset(KeyArray, 0, sizeof(KeyArray)); continue;}

	// 	if (study_start == 1)
	// 	{
	// 		KeyNumSelection = KeyNum;
	// 		studying_flag = 3;
	// 		study_start = 0;
	// 	}else if (studying_flag != 0)
	// 	{
	// 		// put the data into the keydata 2d array
	// 		studying_flag--;
	// 		KeyData[KeyNumSelection][2-studying_flag] = KeyNum;
	// 	}else{
	// 		// combine the three inputs into an array
	// 		// if finished, refresh the keyindex
	// 		if (KeyIndex == 3) {
	// 			KeyIndex = 0;
	// 			memset(KeyArray, 0, sizeof(KeyArray));
	// 		}
	// 		KeyArray[KeyIndex] = KeyNum;
	// 		KeyIndex++;
	// 		// compare the current array with the existing arrays (can be improved)
	// 		uint8_t i; count = 0;
	// 		for (i = 63; i > 0; i--)
	// 		{
	// 			count = 0;
	// 			if (KeyArray[0] == KeyData[i][0]) count++;
	// 			if (KeyArray[1] == KeyData[i][1]) count++;
	// 			if (KeyArray[2] == KeyData[i][2]) count++;
	// 			if (count == 3) {FunctionNum = i; break;}
	// 			// if (memcmp(KeyArray, KeyData[i], 3)) {FunctionNum = i; break;}
	// 		}

	// 	}
			
	// 	if (FunctionNum == 8) {LED1_Turn(); FunctionNum = 0;}
	// 	if (FunctionNum == 9) {LED2_Turn(); FunctionNum = 0;}
	// 	if (FunctionNum == 10) {LED3_Turn(); FunctionNum = 0;}
		
	// }

	while (1) {
		KeyNum = Key_GetNum();

		// Check if no key is pressed or if the same key is pressed again
		if (KeyNum == NO_EVENT_KEY || KeyNum == PrevKey) {
			continue;
		}
		
		display(KeyNum);
		PrevKey = KeyNum;

		// Check for specific key actions
		switch (KeyNum) {
			case START_STUDYING_KEY:
				if (study_start == 0) {
					study_start = 1;
					continue;
				}
				break;
			
			case RESET_RECORDING_KEY:
				KeyIndex = 0;
				memset(KeyArray, 0, sizeof(KeyArray));
				continue;

			default:
				break;
		}

		if (study_start) {
			// Set key for studying
			KeyNumSelection = KeyNum;
			studying_flag = 3;
			study_start = 0;
		} else if (studying_flag != 0) {
			// Put the data into the KeyData 2D array
			studying_flag--;
			KeyData[KeyNumSelection][2 - studying_flag] = KeyNum;
		} else {
			// Combine the three inputs into an array
			if (KeyIndex == 3) {
				KeyIndex = 0;
				memset(KeyArray, 0, sizeof(KeyArray));
			}
			KeyArray[KeyIndex++] = KeyNum;
			
			// Compare the current array with the existing arrays (can be improved)
			uint8_t i, count = 0;
			for (i = 63; i > 0; i--) {
				count = 0;
				if (KeyArray[0] == KeyData[i][0]) count++;
				if (KeyArray[1] == KeyData[i][1]) count++;
				if (KeyArray[2] == KeyData[i][2]) count++;
				if (count == 3) {
					FunctionNum = i;
					break;
				}
			}
		}

		// Perform actions based on the determined function number
		switch (FunctionNum) {
			case 8:
				LED1_Turn();
				FunctionNum = 0;
				break;
			
			case 9:
				LED2_Turn();
				FunctionNum = 0;
				break;

			case 10:
				LED3_Turn();
				FunctionNum = 0;
				break;

			default:
				break;
		}
	}

	
}

