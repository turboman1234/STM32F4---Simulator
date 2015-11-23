#include "stm32f4xx_conf.h"
#include "definitions.h"
#include "adc.h"

int GetButtonState(int buttonNumber);
int GetDigitalInput(int inputNumber);
int GetSwitchState(int switchNumber);
int GetOutputState(int outputNumber);
int GetTrimmerValue(int trimmerNumber);
int GetAnalogInput(int adcNumber);
int GetAnalogOutput(int dacNumber);
void SetDigitalOutput(int outputNumber, int state);
void SetAnalogOutput(int dacOutput, int value);
