#ifndef __SERIAL_H
#define __SERIAL_H

void InitSerial(void);
unsigned char GetByte(int usartID);
int InString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds);
int OutString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds);

#endif
