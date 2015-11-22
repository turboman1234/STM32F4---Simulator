#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "rcc.h"

extern RCC_ClocksTypeDef MYCLOCKS;

int main()
{
    int ledID = 0, state = 0, buttonState = 0;
    
    InitRCC();
    
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    STM_EVAL_LEDInit(LED3);
        
    while(1)
    {
        buttonState = STM_EVAL_PBGetState(BUTTON_USER);
        if(buttonState && state == 0)
        {
            STM_EVAL_LEDOn(LED4);
            state = 1;
        }
        
        buttonState = STM_EVAL_PBGetState(BUTTON_USER);
        if(buttonState && state == 1)
        {
            STM_EVAL_LEDOff(LED4);
            state = 0;
        }
    }
}
