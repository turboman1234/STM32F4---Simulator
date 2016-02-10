#include "stm32f4xx_conf.h"
#include "definitions.h"
#include "usart.h"


void InitSerial(void);
unsigned char GetByte(int usartID);
int InString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds);
int OutString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds);
