#include "stm32f4xx_conf.h"
#include "definitions.h"
#include "VTimer.h"
#include "usart.h"


void InitUSART2(void)
{
    GPIO_InitTypeDef MYGPIO;
    USART_InitTypeDef MYUSART;
    NVIC_InitTypeDef MYNVIC;
    
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    
    /* TX pin*/
    MYGPIO.GPIO_Mode = GPIO_Mode_AF;
    MYGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    MYGPIO.GPIO_Pin = GPIO_Pin_2;
    
    GPIO_Init(GPIOA, &MYGPIO);
    
    /* RX pin */
    MYGPIO.GPIO_Mode = GPIO_Mode_AF;
    MYGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    MYGPIO.GPIO_Pin = GPIO_Pin_3;
    
    GPIO_Init(GPIOA, &MYGPIO);
        
    
    MYUSART.USART_BaudRate = eUsartBaudRate19200;
    MYUSART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    MYUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    MYUSART.USART_Parity = eUsartParityNo;
    MYUSART.USART_StopBits = eUsartStopBits1;
    MYUSART.USART_WordLength = eUsartWordLength8b;
    USART_Init(USART2, &MYUSART);
    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    MYNVIC.NVIC_IRQChannel = USART3_IRQn;
    MYNVIC.NVIC_IRQChannelCmd = ENABLE;
    MYNVIC.NVIC_IRQChannelPreemptionPriority = 0;
    MYNVIC.NVIC_IRQChannelSubPriority = 0;
    USART_ClearFlag(USART2, USART_FLAG_RXNE);
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    NVIC_Init(&MYNVIC);
    
    USART_Cmd(USART2, ENABLE);	
}

void InitUSART3(void)
{
    GPIO_InitTypeDef MYGPIO;
    USART_InitTypeDef MYUSART;
    NVIC_InitTypeDef MYNVIC;
    
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    
    /* TX pin*/
    MYGPIO.GPIO_Mode = GPIO_Mode_AF;
    MYGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    MYGPIO.GPIO_Pin = GPIO_Pin_8;
    
    GPIO_Init(GPIOD, &MYGPIO);
    
    /* RX pin */
    MYGPIO.GPIO_Mode = GPIO_Mode_AF;
    MYGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    MYGPIO.GPIO_Pin = GPIO_Pin_9;
    
    GPIO_Init(GPIOD, &MYGPIO);
        
    
    MYUSART.USART_BaudRate = eUsartBaudRate19200;
    MYUSART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    MYUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    MYUSART.USART_Parity = eUsartParityNo;
    MYUSART.USART_StopBits = eUsartStopBits1;
    MYUSART.USART_WordLength = eUsartWordLength8b;
    USART_Init(USART3, &MYUSART);
    
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    MYNVIC.NVIC_IRQChannel = USART3_IRQn;
    MYNVIC.NVIC_IRQChannelCmd = ENABLE;
    MYNVIC.NVIC_IRQChannelPreemptionPriority = 0;
    MYNVIC.NVIC_IRQChannelSubPriority = 0;
    USART_ClearFlag(USART3, USART_FLAG_RXNE);
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    NVIC_Init(&MYNVIC);
    
    USART_Cmd(USART3, ENABLE);	
}


unsigned char recieveMyUSART(int usartID)
{
    assert_param(IS_USART_ID_VALID(usartID));
    
    unsigned char recvtemp;
    USART_TypeDef* USARTx;
    
    switch(usartID)
    {
    case USART_2:
        USARTx = USART2;
        break;
    case USART_3:
        USARTx = USART3;
        break;
    }
    
    if(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == SET)
    {
        recvtemp = USART_ReceiveData(USARTx);
        return recvtemp;
    }
    return 0;
}


unsigned char sendMyUSART(char *data, unsigned char count, int usartID)
{
    assert_param(IS_USART_ID_VALID(usartID));
    
    unsigned char bytesSend = 0;	
    USART_TypeDef* USARTx;
    
    switch(usartID)
    {
    case USART_2:
        USARTx = USART2;
        break;
    case USART_3:
        USARTx = USART3;
        break;
    }
    
    while(count--)
    {
        SetVTimerValue(TIMER_COMMUNICATION, T_10_MS);
        
        //check if TX buffer is empty
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET && IsVTimerElapsed(TIMER_COMMUNICATION) == NOT_ELAPSED);
        if(IsVTimerElapsed(TIMER_COMMUNICATION) == NOT_ELAPSED)
        {
            USART_SendData(USARTx, *data);
        }
        else 
        {
            break;
        }
        data++;
        bytesSend ++;
    }
    
    
    SetVTimerValue(TIMER_COMMUNICATION, T_10_MS);
    
    //check if TX is done
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET &&  IsVTimerElapsed(TIMER_COMMUNICATION) == NOT_ELAPSED);
       
    return bytesSend;
}

