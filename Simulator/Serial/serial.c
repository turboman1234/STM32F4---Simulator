#include "serial.h"

int InString(unsigned char *Str, int len)
{
    int recieveBytes = 0;
    unsigned char *temp = Str;
    
    while(len > 0)
    {
        *temp = recieveMyUSART(USART_3);
        temp ++;
        len --;
        recieveBytes ++;
    }
    
    return recieveBytes;
}

int outString(unsigned char *Str, int len, int usartID)
{
	int NumBytesWritten = 0;
    
	NumBytesWritten = sendMyUSART((char *) Str, len, usartID);

	if(NumBytesWritten != len)
	{
		return 0x80; //TRANSMIT_TIMEOUT_ERROR;
	}

	return NumBytesWritten;
}

