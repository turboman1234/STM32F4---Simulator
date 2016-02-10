#include "serial.h"

void InitSerial(void)
{
    InitUSART3();
}

unsigned char GetByte(int usartID)
{
    return recieveMyUSART(usartID);
}

//char *Str - pointer to data which will be send
//int len - number of sending data bytes
//int usartID - USART_2 for ModBus and USART_3 fot serial communication RS232
//int timerType - TIMER_XX, MB_MASTER_TIMER, TIMER_COMMUNICATION ...
//int miliseconds - timeout between frames sending - T_10_MS, T_100_MS, T_1_S...
int InString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds)
{
    //    int recieveBytes = 0;
    //        
    //    while(len > 0)
    //    {
    //        *Str = recieveMyUSART(usartID);
    //        Str ++;
    //        len --;
    //        recieveBytes ++;
    //    }
    //    
    //    return recieveBytes;
    
    int x;
    int BytesReceived = 0;
    
    SetVTimerValue(timerType, miliseconds);
    while(IsVTimerElapsed(timerType) == FALSE)
    {		
        x = recieveMyUSART(usartID);		
        isTimerElapsed = IsVTimerElapsed(timerType);
        if(x != -1 && isTimerElapsed == FALSE)
        {
            SetVTimerValue(timerType, miliseconds);
            Str[BytesReceived] = x;
            BytesReceived ++;
        }
    }
    return BytesReceived;
}

//char *Str - pointer to data which will be send
//int len - number of sending data bytes
//int usartID - USART_2 for ModBus and USART_3 fot serial communication RS232
//int timerType - TIMER_XX, MB_MASTER_TIMER, TIMER_COMMUNICATION ...
//int miliseconds - timeout between frames sending - T_10_MS, T_100_MS, T_1_S...
int OutString(unsigned char *Str, int len, int usartID, int timerType, int miliseconds)
{
	int NumBytesWritten = 0;
    
	NumBytesWritten = sendMyUSART((char *) Str, len, usartID, timerType, miliseconds);

	if(NumBytesWritten != len)
	{
		return 0x80; //TRANSMIT_TIMEOUT_ERROR;
	}

	return NumBytesWritten;
}

