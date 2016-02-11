#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "system_stm32f4xx.h"
#include "definitions.h"
#include "rcc.h"
#include "initPeripheral.h"
#include "userLibrary.h"
#include "VTimer.h"


extern RCC_ClocksTypeDef MYCLOCKS;

int trimmerValue, dacValue = 0;
float volts = 0.0;

int main()
{
    int ledID = 0;
    
    InitRCC();
    InitVTimers();
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    
//    //ADC test
//    InitTrimmer(TRIMMER_1);
//    InitDAC(DAC_2, MIN_ANALOG_VALUE_12b);
//        
//    while(1)
//    {
//        
//        trimmerValue = GetTrimmerValue(TRIMMER_1);
//        
//        SetAnalogOutput(DAC_2, trimmerValue * 4);
//        
//        dacValue = GetAnalogOutput(DAC_2);
//        
//        volts = 2.979 * ((float)dacValue / (float)MAX_ANALOG_VALUE_12b);
//    } 
    
    SetVTimerValue(TIMER_1, 500);
    
    ClearVTimer(TIMER_15);
    ClearVTimer(TIMER_10);
    ClearVTimer(TIMER_12);
    while(1)
    {
        if(IsVTimerElapsed(TIMER_1) == ELAPSED)
        {
            STM_EVAL_LEDOff(LED3);
            STM_EVAL_LEDOff(LED4);
            STM_EVAL_LEDOff(LED5);
            STM_EVAL_LEDOff(LED6);
            
            STM_EVAL_LEDOn(ledID);
            
            if(ledID == 3)
            {
                ledID = 0;
            }
            else
            {
                ledID = ledID + 1;
            }
            
            SetVTimerValue(TIMER_1, 500);
        }
                
        VTimerTask();
        
    }
    
}
