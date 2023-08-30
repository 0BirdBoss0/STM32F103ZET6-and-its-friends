#include "stm32f10x.h" // Device header
#include "stdio.h"
#include "string.h"
#include "Delay.h"
#include "LED2.h"
#include "Key2.h"
#include "SevenSeg2.h"
#include "Timer.h"
#include "OLED.h"
#include "Serial.h"
#include "Relay.h"

uint8_t KeyNum;          // The number of the key now pressed
uint8_t PrevKey;         // The previous key pressed
uint8_t FunctionNum;     // The function number that needs to be called
uint8_t KeyNumSelection; // The number of the key that is selected to be the object to edit
uint8_t KeyArray[3];     // The array to hold the temporary key combinations
uint8_t KeyIndex;        // The index of the array to hold the temporary key

uint8_t KeyData[256][3]; // The key data array library

uint8_t TimeSettings[5]; // The time settings of the all five turns of waiting mode
uint8_t TimeIndex;       // The index of the the turns

uint32_t NanoSecond;
uint32_t MicroSecond;
uint32_t MilliSecond;
uint32_t Second;

uint8_t i;
uint8_t count;
uint32_t Score;

enum STATE {
    IDLE,
    STUDYING,
    WAITING,
    RECORDING,
    COMPARING
} state;

int main(void)
{

    // LED Init
    LED_Init();

    // Timer Init
    Timer2_Init();
    Timer3_Init(10000);
    Timer4_Init(10000);
    // Timer5_Init(10000);
    NanoSecond  = 0;
    MicroSecond = 0;
    MilliSecond = 0;
    Second      = 0;

    // Keyboard Init
    Key_Init();
    KeyIndex        = 0;                 // 初始化 按键指针
    PrevKey         = NO_EVENT_KEY;      // 初始化 上一个按键
    KeyNumSelection = NO_EVENT_KEY;      // 初始化 功能选择
    FunctionNum     = 0;                 // 初始化 功能码
    memset(KeyData, 0, sizeof(KeyData)); // 初始化 按键组合记载 为0

    // 7 Segment Display Init
    // 数码管初始化
    HC595_GPIO_Configuration();
    display(0);

    // Flags Init
    // 所需旗帜与状态初始化
    uint8_t studying_flag = 0; // flag to show that the program is studying the new key combo: 0 = no, 1+ = yes
    state                 = IDLE;

    // 485 Serial Communication Init
    Serial_Init();

    // Relay Init
    // 继电器初始化
    Relay_Init();
    Relay_OFF();

    // OLED Init
    // OLED初始化
    OLED_Init();
    OLED_ShowString(1, 1, "Idle Mode");

    Score     = 0;
    TimeIndex = 0;
    memset(TimeSettings, 5, sizeof(TimeSettings)); // 初始化 每轮的等待时间 为5

    while (1) {

        KeyNum = Key_GetNum();

        // Check if no key is pressed or if the same key is pressed again
        if ((KeyNum == NO_EVENT_KEY) || (KeyNum == PrevKey)) continue;

        // OLED_Clear();

        PrevKey = KeyNum;

        // 	// Check for specific key actions
        switch (KeyNum) {

            case 5:
                FunctionNum = 5;
                break;

            case 6:
                FunctionNum = 6;
                Second      = 0;
                MilliSecond = 0;
                display(0);
                LED_ON(0);
                break;

            case 7:
                FunctionNum = 7;
                break;

            case 8:
                FunctionNum = 8;
                break;

            // when key57 is pressed, the program will add the waiting time for the 1st turn.
            // 当57号按键触发，第1轮等待时间 +1s
            case FIRST_TIMER_INCREMENT_KEY:
                OLED_Clear();
                OLED_ShowString(1, 1, "First Turn");
                (TimeSettings[0] >= 9) ? (TimeSettings[0] = 1) : (TimeSettings[0]++);
                OLED_ShowNum(2, 1, TimeSettings[0], 1);
                OLED_ShowString(2, 2, " second(s)");
                continue;

            // when key58 is pressed, the program will add the waiting time for the 2nd turn.
            // 当58号按键触发，第2轮等待时间 +1s
            case SECOND_TIMER_INCREMENT_KEY:
                OLED_Clear();
                OLED_ShowString(1, 1, "Second Turn");
                (TimeSettings[0] >= 9) ? (TimeSettings[1] = 1) : (TimeSettings[1]++);
                OLED_ShowNum(2, 1, TimeSettings[1], 1);
                OLED_ShowString(2, 2, " second(s)");
                continue;

            // when key59 is pressed, the program will add the waiting time for the 3rd turn.
            // 当59号按键触发，第3轮等待时间 +1s
            case THIRD_TIMER_INCREMENT_KEY:
                OLED_Clear();
                OLED_ShowString(1, 1, "Third Turn");
                (TimeSettings[0] >= 9) ? (TimeSettings[2] = 1) : (TimeSettings[2]++);
                OLED_ShowNum(2, 1, TimeSettings[2], 1);
                OLED_ShowString(2, 2, " second(s)");
                continue;

            // when key60 is pressed, the program will add the waiting time for the 4th turn.
            // 当60号按键触发，第4轮等待时间 +1s
            case FOURTH_TIMER_INCREMENT_KEY:
                OLED_Clear();
                OLED_ShowString(1, 1, "Fourth Turn");
                (TimeSettings[0] >= 9) ? (TimeSettings[3] = 1) : (TimeSettings[3]++);
                OLED_ShowNum(2, 1, TimeSettings[3], 1);
                OLED_ShowString(2, 2, " second(s)");
                continue;

            // when key61 is pressed, the program will add the waiting time for the 5th turn.
            // 当61号按键触发，第5轮等待时间 +1s
            case FIFTH_TIMER_INCREMENT_KEY:
                OLED_Clear();
                OLED_ShowString(1, 1, "Fifth Turn");
                (TimeSettings[0] >= 9) ? (TimeSettings[4] = 1) : (TimeSettings[4]++);
                OLED_ShowNum(2, 1, TimeSettings[4], 1);
                OLED_ShowString(2, 2, " second(s)");
                continue;

            // When key62 is pressed, the program will start study mode
            // Study mode: Press 62 - wait n seconds - Record 3 Key Combo - wait (Perhaps 62 Reset) - End
            // 当62号按键触发，启动 “学习模式”
            // 学习模式：按下62 - 等待n秒 - 用户输入由3个按键组成的组合 - 等待用户按下结束或重置 - 结束
            case START_STUDYING_KEY:

                // study_start = 1;
                KeyNumSelection = KeyNum;
                studying_flag   = 4;
                OLED_Clear();
                OLED_ShowString(1, 1, "Studying Mode ");
                OLED_ShowNum(2, 1, KeyNum, 2);
                OLED_ShowNum(2, 4, KeyNumSelection, 2);
                OLED_ShowNum(2, 7, FunctionNum, 2);
                OLED_ShowNum(2, 10, Score, 2);
                state = STUDYING;

                continue;

            // When key63 is pressed, the program will start the normal process mode
            // Normal mode: Press 63 - wait n seconds - Start counting down - Record 3 Key Combo - End (Manually or after countdown ends)
            // 当63号按键触发的时候，启动 “常规模式”
            // 常规模式：先进入一个持续n秒（n的值可设置）的等待阶段，再进入一个持续15秒的记录阶段，在记录阶段中可输入由三位按键组成的按键组合
            // 本次输入的按键组合将在记录阶段结束时与单片机曾经记录过的按键组合比较，输出相应的功能码
            case START_NORMAL_KEY:

                MilliSecond = 0; // 重置计时器
                OLED_Clear();
                OLED_ShowString(1, 1, "Waiting Mode");
                state = WAITING;
                continue;

            // When key64 is pressed, the program will stop either recording or waiting or studying
            // 当64号按键触发，中止等待/记录/学习模式，并结算输入
            case END_KEY:
                memset(KeyArray, 0, sizeof(KeyArray));
                MilliSecond     = 0;
                KeyNumSelection = 0;
                TimeIndex       = 0;
                OLED_Clear();
                OLED_ShowString(1, 1, "IDLE Mode     ");
                OLED_ShowNum(2, 1, KeyNum, 2);
                OLED_ShowNum(2, 4, KeyNumSelection, 2);
                OLED_ShowNum(2, 7, FunctionNum, 2);
                OLED_ShowNum(2, 10, Score, 2);
                OLED_ShowString(4, 1, "              ");
                state = IDLE;
                continue;

                // May expand the specific key funtion here

            default:
                OLED_ShowNum(2, 1, KeyNum, 2);
                break;
        }

        // 基于状态机进行处理
        switch (state) {

            // 处于学习模式时
            case STUDYING:
                OLED_ShowString(1, 1, "Studying Mode ");

                // 用户的第一次输入作为按键组合保存的位置、对应的功能
                if (studying_flag == 4) {
                    KeyNumSelection = KeyNum;
                    studying_flag--;
                    continue;
                }

                studying_flag--;
                KeyData[KeyNumSelection][2 - studying_flag] = KeyNum;
                OLED_ShowNum(4, 1, KeyData[KeyNumSelection][0], 2);
                OLED_ShowNum(4, 4, KeyData[KeyNumSelection][1], 2);
                OLED_ShowNum(4, 7, KeyData[KeyNumSelection][2], 2);
                if (studying_flag == 0) studying_flag = 3;

                break;

            case RECORDING:
                OLED_ShowString(1, 1, "Recording Mode");
                if (KeyIndex == 3) {
                    KeyIndex = 0;
                    memset(KeyArray, 0, sizeof(KeyArray));
                }
                KeyArray[KeyIndex++] = KeyNum;

                OLED_ShowNum(3, 1, KeyArray[0], 2);
                OLED_ShowNum(3, 4, KeyArray[1], 2);
                OLED_ShowNum(3, 7, KeyArray[2], 2);
                break;

            default:
                break;
        }
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {

        Serial_SendByte(0x41);
        PrevKey = NO_EVENT_KEY;

        switch (state) {
            case WAITING: // 当处于Waiting状态时，每秒检查一次计时器并更新OLED显示屏倒计时
                OLED_ShowNum(4, 1, ((((TimeSettings[TimeIndex] * 1000) - MilliSecond) / 1000)), 1);

                // 如果倒计时结束，进入Recording状态并刷新OLED
                if (MilliSecond > (TimeSettings[TimeIndex] * 1000)) {
                    memset(KeyArray, 0, sizeof(KeyArray));
                    OLED_Clear();
                    OLED_ShowString(1, 1, "Recording Mode");
                    MilliSecond = 0;
                    (TimeIndex >= 4) ? (TimeIndex = 0) : (TimeIndex++);
                    state = RECORDING;
                }

                MilliSecond = MilliSecond + 1000;
                break;

            case RECORDING:
                OLED_ShowNum(4, 1, (((RECORD_WAITING_TIME - MilliSecond) / 1000)), 2);
                OLED_ShowString(4, 3, "              ");
                if (MilliSecond > RECORD_WAITING_TIME) {

                    // Compare the current array with the existing arrays (can be improved)
                    i     = 0;
                    count = 0;
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

                    memset(KeyArray, 0, sizeof(KeyArray));
                    MilliSecond = 0;
                    OLED_Clear();
                    OLED_ShowString(1, 1, "Waiting Mode");
                    state = WAITING;
                }
                MilliSecond = MilliSecond + 1000;
                break;
            default:
                break;
        }

        // 根据功能码（按键组合录入的位置）选择相应的要执行的功能
        // 可以是加特定的分数，也可以是点亮某LED
        switch (FunctionNum) {
            case 1:
                LED_ON(3);
                Score += 1;
                FunctionNum = 0;
                display(Score);
                break;
            case 2:
                LED_ON(12);
                Score += 2;
                FunctionNum = 0;
                display(Score);
                break;
            case 3:
                LED_ON(48);
                Score += 3;
                FunctionNum = 0;
                display(Score);
                break;
            case 4:
                LED_ON(192);
                Score += 4;
                FunctionNum = 0;
                display(Score);
                break;
            case 7:
                Relay_ON();
                FunctionNum = 0;
                break;
            case 8:
                Relay_OFF();
                FunctionNum = 0;
                break;

            default:
                break;
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {

        if (FunctionNum == 5) {
            if (MicroSecond > 0xFFFF) MicroSecond = 0;
            LED_ON(MicroSecond);
            MicroSecond = MicroSecond << 1 | 1;

            if (Second > 16) Second = 0;
            display(16 - Second);
            Second++;
        }

        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

// void TIM5_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) {

//         TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
//     }
// }
