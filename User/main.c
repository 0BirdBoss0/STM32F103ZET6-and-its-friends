#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "Delay.h" 
#include "LED.h"
#include "Key.h"
#include "SevenSeg.h"
#include "Timer.h"
#include "OLED.h"
#include "Serial.h"





uint8_t KeyNum;
uint8_t FunctionNum;
uint8_t KeyNumSelection;
uint8_t KeyArray[3];
uint8_t KeyIndex;
uint8_t PrevKey;
uint8_t KeyData[256][3];

uint8_t Second;
uint8_t Second2;

uint8_t i;
uint8_t count;


enum STATE { 
	IDLE,
	STUDYING,
	WAITING,
	RECORDING,
	COMPARING
} state;



int main(void){
	

	//LED Init
	LED_Init();


	// Timer Init
	Timer2_Init();
	Timer3_Init(1000);


	// Keyboard Init
	Key_Init();
	KeyIndex = 0;
	PrevKey = NO_EVENT_KEY;
	KeyNumSelection = NO_EVENT_KEY;
	FunctionNum = 0;
	memset(KeyData, 0, sizeof(KeyData)); 


	// 7 Segment Display Init
	HC595_GPIO_Configuration();
	display(0);
	

	// Flags Init
	uint8_t study_start = 0; 	// flag to show that the user wants to input a new key combo: 	0 = no, 1+ = yes
	uint8_t studying_flag = 0;  // flag to show that the program is studying the new key combo: 0 = no, 1+ = yes
	state = IDLE;

	
	// 485 Serial Communication Init
	Serial_Init();
	// Serial_SendByte(0x41);
	
	// OLED Init
	OLED_Init();
	OLED_ShowString(1,1,"Helloworld");


	while (1) {
		KeyNum = Key_GetNum();
	
		// Check if no key is pressed or if the same key is pressed again
		if (KeyNum == NO_EVENT_KEY || KeyNum == PrevKey) continue;
		
		display(KeyNum);
		OLED_ShowNum(2,1,KeyNum,2);
		PrevKey = KeyNum;

		// Check for specific key actions
		switch (KeyNum) {

			// When key64 is pressed
			case START_STUDYING_KEY:
				study_start = 1; 
				KeyNumSelection = KeyNum;
				studying_flag = 3;
				state = STUDYING;
			
				continue;

			// When key63 is pressed
			case RESET_RECORDING_KEY:
				
				KeyIndex = 0;
				memset(KeyArray, 0, sizeof(KeyArray));
				
				continue;

			// case START_RECORDING_KEY:

			// May expand the specific key funtion here

			default:
				break;
		}




		// switch (state)
		// {
		// 	case IDLE:
		// 		// Combine the three inputs into an array
		// 		if (KeyIndex == 3) {
		// 			KeyIndex = 0;
		// 			memset(KeyArray, 0, sizeof(KeyArray));
		// 		}
		// 		KeyArray[KeyIndex++] = KeyNum;
				
		// 		// Compare the current array with the existing arrays (can be improved)
		// 		i = 0;
		// 		count = 0;
		// 		for (i = 63; i > 0; i--) {
		// 			count = 0;
		// 			if (KeyArray[0] == KeyData[i][0]) count++;
		// 			if (KeyArray[1] == KeyData[i][1]) count++;
		// 			if (KeyArray[2] == KeyData[i][2]) count++;
		// 			if (count == 3) {
		// 				FunctionNum = i;
		// 				break;
		// 			}
		// 		}
		// 		break;

		// 	case STUDYING:
		// 		studying_flag--;
		// 		KeyData[KeyNumSelection][2 - studying_flag] = KeyNum;
		// 		if (studying_flag == 0) state = IDLE;
		// 		break;
		
		// 	default:
		// 		break;
		// }


		if (study_start) {

			OLED_ShowString(3,1,"Studying Mode ");
			// Set key for studying
			KeyNumSelection = KeyNum;
			studying_flag = 3;
			study_start = 0;

		} else if (studying_flag != 0) {
			// Put the data into the KeyData 2D array
			studying_flag--;
			KeyData[KeyNumSelection][2 - studying_flag] = KeyNum;
			
		} else {

			OLED_ShowString(3,1,"Recording Mode");
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

void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		Second++;
		// display(Second);
		Serial_SendByte(0x41);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET )
	{
		Timer3_Init(PrevKey * 100);
		if (Second2 == 8) Second2 = 0;
		GPIO_Write(GPIOF, ~(0x0001 << Second2));
		Second2++;
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	
}
