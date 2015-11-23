#include "userLibrary.h"

int GetButtonState(int buttonNumber)
{
    assert_param(IS_BUTTON_ID_VALID(buttonNumber));
    
    uint8_t buttonState;
    
    switch(buttonNumber)
    {
    case BUTTON_1:
        buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
        break;
    case BUTTON_2:
        buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
        break;
    case BUTTON_3:
        buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
        break;
    case BUTTON_4:
        buttonState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11);
        break;
    case BUTTON_5:
        buttonState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
        break;
    case BUTTON_6:
        buttonState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
        break;
    case BUTTON_7:
        buttonState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);
        break;
    case BUTTON_8:
        buttonState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
        break;
    }
    
    if(buttonState != 0)
    {
        return PRESSED;
    }
    else
    {
        return NOT_PRESSED;
    }
}

int GetDigitalInput(int inputNumber)
{
    assert_param(IS_INPUT_ID_VALID(inputNumber));
    
    uint8_t inputState;
    
    switch(inputNumber)
    {
    case INPUT_1:
        inputState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
        break;
    case INPUT_2:
        inputState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
        break;
    case INPUT_3:
        inputState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
        break;
    case INPUT_4:
        inputState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
        break;
    case INPUT_5:
        inputState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
        break;
    case INPUT_6:
        inputState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
        break;
    case INPUT_7:
        inputState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
        break;
    case INPUT_8:
        inputState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
        break;
    case INPUT_9:
        inputState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
        break;
    case INPUT_10:
        inputState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4);
        break;
    case INPUT_11:
        inputState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
        break;
    case INPUT_12:
        inputState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
        break;
    case INPUT_13:
        inputState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
        break;
    case INPUT_14:
        inputState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
        break;
    case INPUT_15:
        inputState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);
        break;
    case INPUT_16:
        inputState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12);
        break;
    }
    
    if(inputState != 0)
    {
        return ON;
    }
    else
    {
        return OFF;
    }
}

int GetSwitchState(int switchNumber)
{
    assert_param(IS_SWITCH_ID_VALID(switchNumber));
    
    uint8_t switchState;
        
    switch(switchNumber)
    {
    case SWITCH_1:
        switchState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);
        break;
    case SWITCH_2:
        switchState = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
        break;
    }
    
    if(switchState != 0)
    {
        return ON;
    }
    else
    {
        return OFF;
    }
}

int GetOutputState(int outputNumber)
{
    assert_param(IS_OUTPUT_ID_VALID(outputNumber));
    
    uint8_t outputState;
    
    switch(outputNumber)
    {
    case OUTPUT_1:
        outputState = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1);
        break;
    case OUTPUT_2:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_7);
        break;
    case OUTPUT_3:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_9);
        break;
    case OUTPUT_4:
        outputState = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11);
        break;
    case OUTPUT_5:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_15);
        break;
    case OUTPUT_6:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_13);
        break;
    case OUTPUT_7:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_11);
        break;
    case OUTPUT_8:
        outputState = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_3);
        break;
    case OUTPUT_9:
        outputState = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0);
        break;
    case OUTPUT_10:
        outputState = GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10);
        break;
    case OUTPUT_11:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8);
        break;
    case OUTPUT_12:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_10);
        break;
    case OUTPUT_13:
        outputState = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10);
        break;
    case OUTPUT_14:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_14);
        break;
    case OUTPUT_15:
        outputState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_12);
        break;
    case OUTPUT_16:
        outputState = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_9);
        break;
    }
    
    if(outputState != 0)
    {
        return ON;
    }
    else
    {
        return OFF;
    }
}

int GetTrimmerValue(int trimmerNumber)
{
    assert_param(IS_TRIMMER_ID_VALID(trimmerNumber));
    
    u16 trimmerValue;
    
    switch (trimmerNumber)
    {
    case TRIMMER_1:
//        PC1 - ADC3, IN 11
        trimmerValue = GetADCValue(ADC3, 11);
        break;
        
    case TRIMMER_2:
//        PA1 - ADC3, IN 1
        trimmerValue = GetADCValue(ADC3, 1);
        break;
        
    case TRIMMER_3:
//        PC2 - ADC3, IN 12
        trimmerValue = GetADCValue(ADC3, 12);
        break;
    }
    
    return (int)trimmerValue;
}

int GetAnalogInput(int adcNumber)
{
    assert_param(IS_ADC_ID_VALID(adcNumber));
    
    u16 adcValue;
    
    switch (adcNumber)
    {
    case ADC_1:
//        PC4 - ADC1, IN 14
        adcValue = GetADCValue(ADC1, 14);
        break;
        
    case ADC_2:
//        PC5 - ADC2, IN 15
        adcValue = GetADCValue(ADC2, 15);
        break;
    }
    
    return (int)adcValue;
}

int GetAnalogOutput(int dacNumber)
{
    assert_param(IS_DAC_ID_VALID(dacNumber));
    
    uint16_t dacValue;
    
    switch(dacNumber)
    {
    case DAC_1:
        dacValue = DAC_GetDataOutputValue(DAC_Channel_1);
        break;
    case DAC_2:
        dacValue = DAC_GetDataOutputValue(DAC_Channel_2);
        break;
    }
    
    return (int)dacValue;
}

void SetDigitalOutput(int outputNumber, int state)
{
    assert_param(IS_OUTPUT_ID_VALID(outputNumber));
    assert_param(IS_OUTPUT_STATE_VALID(state));
        
    switch(outputNumber)
    {
    case OUTPUT_1:
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
        break;
    case OUTPUT_2:
        GPIO_SetBits(GPIOE, GPIO_Pin_7);
        break;
    case OUTPUT_3:
        GPIO_SetBits(GPIOE, GPIO_Pin_9);
        break;
    case OUTPUT_4:
        GPIO_SetBits(GPIOB, GPIO_Pin_11);
        break;
    case OUTPUT_5:
        GPIO_SetBits(GPIOE, GPIO_Pin_15);
        break;
    case OUTPUT_6:
        GPIO_SetBits(GPIOE, GPIO_Pin_13);
        break;
    case OUTPUT_7:
        GPIO_SetBits(GPIOE, GPIO_Pin_11);
        break;
    case OUTPUT_8:
        GPIO_SetBits(GPIOC, GPIO_Pin_3);
        break;
    case OUTPUT_9:
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        break;
    case OUTPUT_10:
        GPIO_SetBits(GPIOD, GPIO_Pin_10);
        break;
    case OUTPUT_11:
        GPIO_SetBits(GPIOE, GPIO_Pin_8);
        break;
    case OUTPUT_12:
        GPIO_SetBits(GPIOE, GPIO_Pin_10);
        break;
    case OUTPUT_13:
        GPIO_SetBits(GPIOB, GPIO_Pin_10);
        break;
    case OUTPUT_14:
        GPIO_SetBits(GPIOE, GPIO_Pin_14);
        break;
    case OUTPUT_15:
        GPIO_SetBits(GPIOE, GPIO_Pin_12);
        break;
    case OUTPUT_16:
        GPIO_SetBits(GPIOA, GPIO_Pin_9);
        break;
    }
    
    return;
}

void SetAnalogOutput(int dacOutput, int value)
{
    assert_param(IS_DAC_ID_VALID(dacNumber));
    
    if(value >= 0 && value <= 4095)
    {    
        switch(dacOutput)
        {
        case DAC_1:
            DAC_SetChannel1Data(DAC_Channel_1, value);
            break;
        case DAC_2:
            DAC_SetChannel1Data(DAC_Channel_2, value);
            break;
        }
    }
}

