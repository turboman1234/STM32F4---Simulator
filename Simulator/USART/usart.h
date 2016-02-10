typedef enum {
    eUsartBaudRate2400 = 2400,
    eUsartBaudRate9600 = 9600,
    eUsartBaudRate19200 = 19200,
    eUsartBaudRate38400 = 38400,
    eUsartBaudRate57600 = 57600,
    eUsartBaudRate115200 = 115200
}tUsartBaudRate;

typedef enum {
    eUsartParityNo = USART_Parity_No,
    eUsartParityEven = USART_Parity_Even,
    eUsartParityOdd = USART_Parity_Odd
}tUsartParity;

typedef enum {
    eUsartStopBits1 = USART_StopBits_1,
    eUsartStopBits0_5 = USART_StopBits_0_5,
    eUsartStopBits1_5 = USART_StopBits_1_5,
    eUsartStopBits2 = USART_StopBits_2
}tUsartStopBits;

typedef enum {
    eUsartWordLength8b = USART_WordLength_8b,
    eUsartWordLength9b = USART_WordLength_9b
}tUsartWordLength;



void InitUSART1(void);
void InitUSART3(void);
unsigned char recieveMyUSART(int usartID);
unsigned char sendMyUSART(char *data, unsigned char count, int usartID, int timerType, int miliseconds);
void USART2_IRQHandler(void);
