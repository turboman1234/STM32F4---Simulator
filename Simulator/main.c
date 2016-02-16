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

 void TestLEDsButtonsAndSwitches(void);


int trimmerValue, dacValue = 0;
float volts = 0.0;

int main()
{   
    
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
    
    TestLEDsButtonsAndSwitches();
    
}
 void TestLEDsButtonsAndSwitches(void)
 {    
    InitRCC();
    InitVTimers();
    
    InitButton(BUTTON_1);
    InitButton(BUTTON_2);
    InitButton(BUTTON_3);
    InitButton(BUTTON_4);
    InitButton(BUTTON_5);
    InitButton(BUTTON_6);
    InitButton(BUTTON_7);
    InitButton(BUTTON_8);
    
    InitLED(LED_1);
    InitLED(LED_2);
    InitLED(LED_3);
    InitLED(LED_4);
    InitLED(LED_5);
    InitLED(LED_6);
    InitLED(LED_7);
    InitLED(LED_8);
    
    InitSwitch(SWITCH_1);
    InitSwitch(SWITCH_2);
    
    int ledID = LED_1;
    
    SetVTimerValue(TIMER_1, 500);
    
    while(1)
    {
        if(IsVTimerElapsed(TIMER_1) == ELAPSED)
        {
            // set all LEDs to OFF state
            SetLED(LED_1, OFF);
            SetLED(LED_2, OFF);
            SetLED(LED_3, OFF);
            SetLED(LED_4, OFF);
            SetLED(LED_5, OFF);
            SetLED(LED_6, OFF);
            SetLED(LED_7, OFF);
            SetLED(LED_8, OFF);
            
            SetLED(ledID, ON);
            
            if(ledID == LED_8)
            {
                ledID = LED_1;
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
