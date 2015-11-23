#include "stm32f4xx_conf.h"

void Init_ADC1(void);
void Init_ADC2(void);
void Init_ADC3(void);
u16 GetADCValue(ADC_TypeDef* ADCx, int channel);

