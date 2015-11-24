#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "rcc.h"
#include "definitions.h"
#include "initPeripheral.h"
#include "userLibrary.h"

extern RCC_ClocksTypeDef MYCLOCKS;

int trimmerValue, dacValue = 0;
float volts = 0.0;

int main()
{
    InitRCC();
        
    //ADC test
    InitTrimmer(TRIMMER_1);
    InitDAC(DAC_2, MIN_ANALOG_VALUE_12b);
        
    while(1)
    {
        
        trimmerValue = GetTrimmerValue(TRIMMER_1);
        
        SetAnalogOutput(DAC_2, trimmerValue * 4);
        
        dacValue = GetAnalogOutput(DAC_2);
        
        volts = 2.979 * ((float)dacValue / (float)MAX_ANALOG_VALUE_12b);
    }      
}
