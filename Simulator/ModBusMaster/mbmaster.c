#include "definitions.h"
#include "mbcrc.h"
#include "serial.h"
#include "mbmaster.h"

unsigned char QueryBuffer[QUERY_MAX_SIZE];
unsigned char MBMasterResponseBuffer[RESPONSE_MAX_SIZE];

int MBMasterQueryBufferLenght;

/*
    This function writes in slave's holding registers
    unsigned char slaveID - recieved slave's address,
    unsigned char startAddress - it is the address of the holding register from which will be starting write operation,
    unsigned char registersCount - how many registers will be written,
    unsigned short *holdingRegistersValues - values, which will be written serialy from first to the last holding registers
*/
void PresetMultipleRegisters(unsigned char slaveID, unsigned char startAddress, unsigned char registersCount, unsigned short *holdingRegistersValues)
{
    int i, queryLenght = 0;
    unsigned int crc;
    unsigned char temp;
    
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 16;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = startAddress;
    QueryBuffer[4] = 0;
    QueryBuffer[5] = registersCount;
    QueryBuffer[6] = registersCount * sizeof(unsigned short);
    
    for(i = 0; i < registersCount; i++)
    {
        //get Data Hi
        temp = (holdingRegistersValues[i] * 0xFF00) >> 8;
        QueryBuffer[2*i + 7] = temp;
        
        // get Data Lo
        temp = holdingRegistersValues[i] * 0x00FF;
        QueryBuffer[2*i + 8] = temp;
    }
    
    queryLenght = 7 + registersCount * sizeof(unsigned short);
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}

/*
    This function sets/resets multuple coils
    
    unsigned char slaveID - recieved slave's address,
    unsigned char coilAddress - first coil from which write operation starts,
    unsigned char quantityOfCoils - count of coils to be written,
    unsigned short coilsData - it saves new coils' status; firs coil is lowest significant bit(0000 000*)
*/
void ForceMultipleCoils(unsigned char slaveID, unsigned char coilAddress, unsigned char quantityOfCoils, unsigned short coilsData)
{
    int queryLenght = 0;
    unsigned int crc;
        
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 15;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = coilAddress;
    QueryBuffer[4] = 0;
    QueryBuffer[5] = quantityOfCoils;
    QueryBuffer[6] = (quantityOfCoils / 8) ? 2:1;
    QueryBuffer[7] = coilsData * 0x00FF;
    
    queryLenght = 8;
    
    if(QueryBuffer[6] == 2)
    {
        QueryBuffer[8] = (coilsData * 0xFF00) >> 8;
        queryLenght = 9;
    }
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}


/*
    This function sets single coil
    unsigned char slaveID - recieved slave's address,
    unsigned char coilAddress - address of the coil, which will be set or reset, 
    unsigned char forceCommand - 0xFF - set, 0x00 - reset
*/
void ForceSingleCoil(unsigned char slaveID, unsigned char coilAddress, unsigned char forceCommand)
{
    int queryLenght;
    unsigned int crc;
    
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 5;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = coilAddress;
    QueryBuffer[4] = forceCommand;
    QueryBuffer[5] = 0;
    
    queryLenght = 6;
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}

/*
    This function reads holding registers
    unsigned char slaveID - recieved slave's address,
    unsigned char startingAddress - register's address from wich reading starts,
    unsigned char holdingRegistersCount - count of registers, which will be written
*/
void ReadHoldingRegisters(unsigned char slaveID, unsigned char startingAddress, unsigned char holdingRegistersCount)
{
    int queryLenght;
    unsigned int crc;
    
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 3;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = startingAddress;
    QueryBuffer[4] = 0;
    QueryBuffer[5] = holdingRegistersCount;
    
    queryLenght = 6;
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}

/*
    This function reads digital inputs
    unsigned char slaveID - recieved slave's address,
    unsigned char startingAddress - input's address from wich reading starts,
    unsigned char inputsCount - count of inputs, which will be read
*/
void ReadInputStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char inputsCount)
{
    int queryLenght;
    unsigned int crc;
    
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 2;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = startingAddress;
    QueryBuffer[4] = 0;
    QueryBuffer[5] = inputsCount;
    
    queryLenght = 6;
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}

/*
    This function reads coils' status
    unsigned char slaveID - recieved slave's address,
    unsigned char startingAddress - coil's address from wich reading starts,
    unsigned char inputsCount - count of coils, which will be read
*/
void ReadCoilStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char coilsCount)
{
    int queryLenght;
    unsigned int crc;
    
    QueryBuffer[0] = slaveID;
    QueryBuffer[1] = 1;
    QueryBuffer[2] = 0;
    QueryBuffer[3] = startingAddress;
    QueryBuffer[4] = 0;
    QueryBuffer[5] = coilsCount;
    
    queryLenght = 6;
    
    crc = usMBCRC16(QueryBuffer, queryLenght);
    
    QueryBuffer[queryLenght + 0] = (unsigned char) crc;
    QueryBuffer[queryLenght + 1] = (unsigned char) (crc >> 8);
    
    MBMasterQueryBufferLenght = queryLenght + 2;
}


void MBMaster(void)
{
   int bytesRead = 0, bytesWritten;
   int result = 0;	

   //USART_2 must be used   
   bytesWritten = OutString(QueryBuffer, MBMasterQueryBufferLenght, USART_2, MB_MASTER_TIMER, T_10_MS);//??????????????????????does timing Ok?????????????????
   if(bytesWritten != MBMasterQueryBufferLenght)
   {
       return;
   }
   
   bytesRead = GetMBAnswer(MBMasterResponseBuffer);
   
   //bytesRead < 0 when there is error in recieving response
   if(bytesRead >= 0)
   {
       result = MBParseBuffer(MBMasterResponseBuffer, QueryBuffer, bytesRead);		
       if(result == 0)
       {
           //do something with responce
       }
   }
   return;
}

int GetMBAnswer(unsigned char *Buffer)
{
   int BytesRead = 0;
   
   //USART_2 must be used   
   BytesRead = InString(Buffer, USART_2, MB_MASTER_TIMER, T_100_MS*100);//??????????????????????does timing Ok?????????????????
   
   if(BytesRead == -1) // Error condition
   {
       return BUFFER_OVERRUN_ERROR; //Buffer Overload
   }
   if(BytesRead == 0) // No bytes read -> We have a serial port timeout
   {
       return DEVICE_TIMEOUT_ERROR;
   }
   
   return BytesRead;
}

int MBParseBuffer(unsigned char *Buffer, unsigned char *CommandArray, int bytesRead)
{
   if( bytesRead > 0)
   {
       if( usMBCRC16( Buffer, bytesRead ) == 0)
       {
           if(Buffer[0] == CommandArray[0]) //Colleced responce is from the same device as expected
           {
               if(Buffer[1] == CommandArray[1]) //Responce to the same command
               {
                   if(Buffer[1] == 1 || Buffer[1] == 2 || Buffer[1] == 3) //if command is reading ...
                   {
                       if(Buffer[2] == bytesRead - PACKET_HEADER_AND_CRC) // Message size correspond to number of the byte read //MS = BR - CRC(2) - HEAD(2) = BR - 4
                       {
                           return 0; // All seems to be OK
                       }
                       else
                       {
                           return PACKET_SIZE_MISMATCH_ERROR;
                       }
                   }
                   else if(Buffer[1] == 5 || Buffer[1] == 15 || Buffer[1] == 16) //if command is writting ...
                   {
                       if(Buffer[2] == CommandArray[2] && Buffer[3] == CommandArray[3] && Buffer[4] == CommandArray[4] && Buffer[5] == CommandArray[5])
                       {
                           return 0; //All it seems to be OK
                       }
                       else
                       {
                           return PACKET_SIZE_MISMATCH_ERROR;
                       }
                   }
               }
               else if(Buffer[1] == (CommandArray[1] + 0x80)) //Error code returned
               {
                   return SPECIFIC_MODBUS_ERROR;
               }
               else
               {
                   return WRONG_DEVICE_RESPONDED;
               }
           }
           else
           {
               return WRONG_DEVICE_RESPONDED;
           }
       }
       else
       {
           return BAD_CRC_ERROR;
       }
   }
   else
   {
       return DEVICE_TIMEOUT_ERROR;
   }
}
