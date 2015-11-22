#include "stm32f4xx_conf.h"
#include "adc.h"

//ADC1 initianilize
void Init_ADC1(void)
{
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
     
    /* Enable ADC1 clock ********************************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
     
    /* ADC Common Init **********************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
     
    /* ADC1 Init ****************************************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);
}

//ADC2 initianilize
void Init_ADC2(void)
{
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
     
    /* Enable ADC1 clock ********************************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
     
    /* ADC Common Init **********************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
     
    /* ADC2 Init ****************************************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_EOCOnEachRegularChannelCmd(ADC2, ENABLE);
    ADC_Cmd(ADC2, ENABLE);
    ADC_SoftwareStartConv(ADC2);
}

//ADC3 initianilize
void Init_ADC3(void)
{
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
     
    /* Enable ADC1 clock ********************************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
     
    /* ADC Common Init **********************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
     
    /* ADC1 Init ****************************************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);
    ADC_EOCOnEachRegularChannelCmd(ADC3, ENABLE);
    ADC_Cmd(ADC3, ENABLE);
    ADC_SoftwareStartConv(ADC3);
}

//Get ADC1 Value
u16 GetADCValue(int chan)
{
    u16 res;
    ADC_RegularChannelConfig(ADC1, chan, 1, ADC_SampleTime_56Cycles);
    
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);
    
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
    
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    
    res = ADC_GetConversionValue(ADC1);
    
    ADC_Cmd(ADC1, DISABLE);
    
    return res;
}
