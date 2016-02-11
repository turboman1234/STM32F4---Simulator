#ifndef __USERLIBRARY_H
#define __USERLIBRARY_H

int GetButtonState(int buttonNumber);
int GetDigitalInput(int inputNumber);
int GetSwitchState(int switchNumber);
int GetOutputState(int outputNumber);
int GetTrimmerValue(int trimmerNumber);
int GetAnalogInput(int adcNumber);
int GetAnalogOutput(int dacNumber);
void SetDigitalOutput(int outputNumber, int state);
void SetAnalogOutput(int dacOutput, int value);

#endif
