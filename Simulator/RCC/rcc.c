#include "stm32f4xx_conf.h"
#include "rcc.h"

RCC_ClocksTypeDef MYCLOCKS;

void InitRCC(void)
{
    // set needed frequencies
    
    //start oscilator
    RCC_HSICmd(ENABLE);
    
    //wait for HSI oscilator start working
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);
    
    //choose HSI clock source
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    
    //set AHB clock - 168, MHz
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    
    //set APB1 clock 24, MHz
    RCC_PCLK1Config(RCC_HCLK_Div8);
    
    //set APB2 clock 84, MHz
    RCC_PCLK2Config(RCC_HCLK_Div2);   
    
     // Show current FREQ in Hz (for DEBUG purposes)
    RCC_GetClocksFreq(&MYCLOCKS);
}


