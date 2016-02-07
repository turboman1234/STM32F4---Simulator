#include "stm32f4xx_conf.h"
#include "mbcrc.h"
#include "mbslave.h"
#include "serial.h"
#include "mytim.h"
#include "definitions.h"

static volatile unsigned short MBRcvBufferPos;
static volatile unsigned short MBSndBufferPos;
static volatile int ActiveSlaveIndex = INVALID_SLAVE_INDEX;

unsigned short HoldingRegisters[HOLDING_REGISTERS_NUMBER];

ModBusSlaveUnit ModBusSlaves[MAX_MODBUS_SLAVE_DEVICES];
unsigned char RecieveBuffer[PACKET_SIZE];
unsigned char ResponseBuffer[RESPONSE_SIZE];

typedef enum
{
    EV_FRAME_RECEIVED,          /*!< Frame received. */
    EV_EXECUTE,                 /*!< Execute function. */
} eMBEventType;

typedef enum
{
    STATE_RX_IDLE,              /*!< Receiver is in idle state. */
    STATE_RX_RCV,               /*!< Frame is beeing received. */
} eMBRcvState;

typedef enum
{
    STATE_TX_IDLE,              /*!< Transmitter is in idle state. */
    STATE_TX_XMIT               /*!< Transmitter is in transfer state. */
} eMBSndState;

volatile eMBEventType MBQueuedEvent;
volatile BOOL    MBEventInQueue;

static volatile eMBSndState MBSndState;
static volatile eMBRcvState MBRcvState;

// ..................UART_RX..........................

/*
    Initialize all Slaves
*/
void InitNewMBSlaveDevices(void)
{
    int i;
    
    for(i = 0; i < MAX_MODBUS_SLAVE_DEVICES; i++)
    {
        ModBusSlaves[i].address = i + 1;
        ModBusSlaves[i].isSlaveActive = FALSE;
        ClearModBusSlaveMemory(ModBusSlaves[i].inputs, INPUTS_NUMBER);
        ClearModBusSlaveMemory(ModBusSlaves[i].outputs, OUTPUTS_NUMBER);
        ClearModBusSlaveMemory((unsigned char *)ModBusSlaves[i].holdingRegisters, HOLDING_REGISTERS_NUMBER * sizeof(unsigned short));
        ClearModBusSlaveMemory(ModBusSlaves[i].recieveBuffer, PACKET_SIZE);
        ClearModBusSlaveMemory(ModBusSlaves[i].responseBuffer, RESPONSE_SIZE);
    }
}

/*
    Clear means fillinig with 0 'size' count in pointed memory

    pMemory - pointer to memory which must be cleared
    size - number of cells from wanted memory

    When it is needed to be cleared HoldingRegisters (shor data type) firs casting, next size = sizeof(short) * HoldRegNumb;
*/
void ClearModBusSlaveMemory(unsigned char *pMemory, int size)
{
    int  i;
    
    for(i = 0; i < size; i++)
    {
        *pMemory = 0;
        pMemory++;
    }
}

/*
    This function copies 'cellsNumber' from 'source' in 'destination'
*/

void CopyModBusMemory(unsigned char *source, unsigned char *destination, unsigned short cellsNumber)
{
    int i;
    
    for(i = 0; i < cellsNumber; i++)
    {
        *destination = *source;
        destination++;
        source++;
    }
}

/*
    This function recognizes for which of all slaves is addressed the current message and sets global int ActiveSlaveAddress with found slave.
    If it's not found slave ActiveSlaveAddress = INVALID_SLAVE_ADDRESS
    The function returns TRUE - recieve address is valid, FALSE - recive address is not valid
    unsigned char recieveAddress - first byte from input message
*/
BOOL MBSlaveAddressRecognition(unsigned char recieveAddress)
{
    int i;
    
    BOOL isRecieveAddressValid = FALSE;
    
    for(i = 0; i < MAX_MODBUS_SLAVE_DEVICES; i++)
    {
        if(ModBusSlaves[i].address == recieveAddress)
        {
            ModBusSlaves[i].isSlaveActive = TRUE;
            isRecieveAddressValid = TRUE;
            ActiveSlaveIndex = i;
            break;
        }
    }
    
    return isRecieveAddressValid;
}

void MBInit(void)
{    
    MBRcvState = STATE_RX_IDLE;
    MBSndState = STATE_TX_IDLE;  
    
    InitNewMBSlaveDevices();
}	

void MBPollSlave( void )
{
    static unsigned char RcvAddress;
    unsigned int crc;
    BOOL isRcvAddressValid;
    
    eMBEventType eEvent;
    
    if( MBEventInQueue )
    {
        eEvent = MBQueuedEvent;
        MBEventInQueue = FALSE;
        
        switch ( eEvent )
        {
        case EV_FRAME_RECEIVED:
            { 
                RcvAddress = RecieveBuffer[0];
                isRcvAddressValid = MBSlaveAddressRecognition(RcvAddress);
                
                if(isRcvAddressValid == TRUE)
                {	
                    //copy global recieveBuffer in active slave's recieveBuffer for regular slave simulation
                    CopyModBusMemory(RecieveBuffer, ModBusSlaves[ActiveSlaveIndex].recieveBuffer, MBRcvBufferPos);
                    
                    crc = usMBCRC16((unsigned char *) ModBusSlaves[ActiveSlaveIndex].recieveBuffer, MBRcvBufferPos);
                    if( crc == 0 )
                    {
                        MBEventInQueue = TRUE;
                        MBQueuedEvent = EV_EXECUTE;     
                    } 
                }
                break;
                
            case EV_EXECUTE:
                {	
                    MB_handle_request();
                    break;
                }
            }
        }
    }
}

void MBReceiveFSM( void )
{
    signed char Byte;
    BOOL isRecieveAddressValid;
    
    Byte = (signed char)GetByte(USART_2);
    
    switch ( MBRcvState )
    {		
    case STATE_RX_IDLE:
        MBRcvBufferPos = 0;
        
        RecieveBuffer[MBRcvBufferPos++] = Byte;
        MBRcvState = STATE_RX_RCV;
        
        ModBusTimerEnable(10);
        break;
        
    case STATE_RX_RCV:
        if( MBRcvBufferPos < PACKET_SIZE )
        {
            RecieveBuffer[MBRcvBufferPos++] = Byte;
        }
        ModBusTimerEnable(T_10_MS);
        break;
    }	
}

void MB_handle_request( void )
{
    int mblen;
    unsigned int crc;
    unsigned int cnt = 0;
    
    //Clearing Response
    ClearModBusSlaveMemory(ResponseBuffer, RESPONSE_SIZE);
    ClearModBusSlaveMemory(ModBusSlaves[ActiveSlaveIndex].responseBuffer, RESPONSE_SIZE);
    
    mblen = 0;
    
    if(ModBusSlaves[ActiveSlaveIndex].recieveBuffer[0] == ModBusSlaves[ActiveSlaveIndex].address)
    {
        switch(ModBusSlaves[ActiveSlaveIndex].recieveBuffer[1])
        {
        case 1:
            mblen = process_cmd1();
            break;
        case 2:
            mblen = process_cmd2();
            break;
        case 3:
            mblen = process_cmd3();
            break;
        case 5:
            mblen = process_cmd5();
            break;
        case 15:
            mblen = process_cmd15();
            break;
        case 16:
            mblen = process_cmd16();
            break;
        default:
            return;
        }
        MBSndState = STATE_TX_XMIT;
    }
    
    if( MBSndState == STATE_TX_XMIT  )
    {
        crc = usMBCRC16(ResponseBuffer, mblen);
        ResponseBuffer[mblen + 0] = (unsigned char) crc;
        ResponseBuffer[mblen + 1] = (unsigned char) (crc >> 8);	
        MBSndBufferPos = mblen + 2; //2 - CRC_LEN
        
        //copy global ResponseBuffer in active slave's response buffer for regular slave simulation.
        CopyModBusMemory(ResponseBuffer, ModBusSlaves[ActiveSlaveIndex].responseBuffer, MBSndBufferPos);
    }
}

void MBTimerExpired( void )
{
    switch ( MBRcvState )
    {
    case STATE_RX_RCV:
        {
            MBEventInQueue = TRUE;
            MBQueuedEvent = EV_FRAME_RECEIVED;
            break;
        }
    default:  ;
    }
    ModBusTimerDisable();
    MBRcvState = STATE_RX_IDLE;
}

void MB_slave_transmit( void )
{
    if( MBSndState == STATE_TX_XMIT )
    {
        outString(ResponseBuffer, MBSndBufferPos, USART_2);			
        MBSndState = STATE_TX_IDLE;
    }
}

//Read Outputs
char process_cmd1(void)
{
    unsigned char outputs;
    unsigned char temp;
    unsigned char bytesCount;
    
    if(RecieveBuffer[2] != 0) 
    {
        return 0; //check START ADDRESS HI is 0
    }
    if(RecieveBuffer[3] > OUTPUTS_NUMBER) 
    {
        return 0;  //check START ADDRESS LO is [0:3]
    }
    if(RecieveBuffer[4] != 0) 
    {
        return 0; //check No of POINTS HI is 0
    }
    if((OUTPUTS_NUMBER - RecieveBuffer[3]) < RecieveBuffer[5]) 
    {
        return 0; //check No of POINTS LO
    }
    
    //take desired action
    outputs = GetDInput() >> RecieveBuffer[3];
    temp = (1 << RecieveBuffer[5]) - 1;
    outputs &= temp;
    bytesCount = (RecieveBuffer[5] / 8) ? 2 : 1;
    
    //compose response
    Response[0] = RecieveBuffer[0]; // SLAVEID - same (already confirmed)
    Response[1] = RecieveBuffer[1]; // COMMANDID - same (already confirmed)
    Response[2] = bytesCount; // BYTECOUNT - is at max 2 bytes as we have 16 outputs
    Response[3] = outputs;
    
    return bytesCount + 3; //length of response;
}

//Read Discrete Input
char process_cmd2(void)
{
    
}

//Read Holding Registeers
char process_cmd3(void)
{
    unsigned char inputs;
    unsigned char temp;
    int i;
	
    if(Buffer[2] != 0) 
	{
		return 0; //check START ADDRESS HI is 0
	}
    if(Buffer[3] > HOLDING_REGISTERS_NUMBER) 
	{
		return 0;  //check START ADDRESS LO is < HOLDING_REGISTERS_NUMBER
	}
    if(Buffer[4] != 0) 
	{
		return 0; //check no of points hi is 0
	}
    if((HOLDING_REGISTERS_NUMBER - Buffer[3]) < Buffer[5]) 
	{
		return 0; //check No of POINTS LO
	}    
        
    //compose response
    Response[0] = Buffer[0]; // SLAVEID - same (already confirmed)
    Response[1] = Buffer[1]; // COMMANDID - same (already confirmed)
    Response[2] = Buffer[5] * 2; // BYTECOUNT - is at max 1 byte as we have only 4 relays
	
	for(i = 0; i < Buffer[5]; i ++)
	{
		Response[3 + i * 2] = HoldingRegisters[i + Buffer[3]] >> 8;
		Response[4 + i * 2] = HoldingRegisters[i + Buffer[3]];
	}
	
    return 3 + Buffer[5] * 2;
}

//Write Single Coil
char process_cmd5(void)
{
    if(Buffer[2] != 0)
    {
        return 0; //check COIL ADDRESS HI is 0
    }
    if(Buffer[3] > 3) 
    {
        return 0;  //check COIL ADDRESS LO is [0:3]
    }
    if(Buffer[4] != 0xFF && Buffer[4] != 0x00) 
    {
        return 0; //check DATA HI
    }
    if(Buffer[5] != 0x00) 
    {
        return 0; //check DATA LO
    }
    
    //take desired action
    if(Buffer[4] == 0xFF)
    {
        // set output on address (Buffer[3]+1)
    }
    else 
    {
        // reset output on address (Buffer[3]+1)
    }
    
    //compose response
    Response[0] = Buffer[0];
    Response[1] = Buffer[1];
    Response[2] = Buffer[2];
    Response[3] = Buffer[3];
    Response[4] = Buffer[4];
    Response[5] = Buffer[5];
    
    return 6;
}

//Write Multiple Coils
char process_cmd15(void)
{
    unsigned char relays, count;
    
    if(Buffer[2] != 0) 
    {
        return 0; //check COIL ADDRESS HI
    }
    if(Buffer[3] > 3) 
    {
        return 0; //check COIL ADDRESS LO is [0:3]
    }
    if(Buffer[4] != 0) 
    {
        return 0; //check QUANTITY HI
    }
    if((4 - Buffer[3]) < Buffer[5]) 
    {
        return 0; //check QUANTITY LO
    }
    if(Buffer[6] != 1) //???????????????????????????????????????????????????
    {
        return 0; // check BYTE COUNT
    }
    
    //take desired action
    relays = Buffer[7] << Buffer[3];
    count = Buffer[5];
    switch(Buffer[3])
    {
    case 0:
        if(relays & 0x01) ctrl_relay(REL1OUT, SET);
        else ctrl_relay(REL1OUT, RESET);
        if((--count) == 0) break;
    case 1:
        if(relays & 0x02) ctrl_relay(REL2OUT, SET);
        else ctrl_relay(REL2OUT, RESET);
        if((--count) == 0) break;
    case 2:
        if(relays & 0x04) ctrl_relay(REL3OUT, SET);
        else ctrl_relay(REL3OUT, RESET);
        if((--count) == 0) break;
    case 3:
        if(relays & 0x08) ctrl_relay(REL4OUT, SET);
        else ctrl_relay(REL4OUT, RESET);
    }

    //compose response
    Response[0] = Buffer[0];
    Response[1] = Buffer[1];
    Response[2] = Buffer[2];
    Response[3] = Buffer[3];
    Response[4] = Buffer[4];
    Response[5] = Buffer[5];
    
    return 6;
}

//Write Holding Registers
char process_cmd16(void)
{
    unsigned char relays, count, i;
    
    if(Buffer[2] != 0) 
	{
		return 0; //check START ADDRESS HI is 0
	}
    if(Buffer[3] > HOLDING_REGISTERS_NUMBER) 
	{
		return 0;  //check START ADDRESS LO is < HOLDING_REGISTERS_NUMBER
	}
    if(Buffer[4] != 0) 
	{
		return 0; //check no of points hi is 0
	}
    if((HOLDING_REGISTERS_NUMBER - Buffer[3]) < Buffer[5]) 
	{
		return 0; //check No of POINTS LO
	}  
	
	for (i = 0; i < Buffer[5]; i ++)
	{
		HoldingRegisters[Buffer[3] + i] = Buffer[7 + i * 2] << 8;
		HoldingRegisters[Buffer[3] + i] |= Buffer[8 + i * 2];
	}	

    //compose response
    Response[0] = Buffer[0];
    Response[1] = Buffer[1];
    Response[2] = Buffer[2];
    Response[3] = Buffer[3];
    Response[4] = Buffer[4];
    Response[5] = Buffer[5];
    
    return 6;
}
