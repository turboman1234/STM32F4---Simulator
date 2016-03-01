#ifndef __MBMASTER_H
#define __MBMASTER_H

#define QUERY_MAX_SIZE                  256
#define RESPONSE_MAX_SIZE               256


#define BUFFER_OVERRUN_ERROR		-1
#define DEVICE_TIMEOUT_ERROR		-2
#define BAD_CRC_ERROR			-3
#define WRONG_DEVICE_RESPONDED		-4
#define PACKET_SIZE_MISMATCH_ERROR	-5
#define SPECIFIC_MODBUS_ERROR		-6
#define SERIAL_PORT_ERROR		-7
#define TRANSMIT_TIMEOUT_ERROR		-8

#define PACKET_HEADER_AND_CRC	        5

void PresetMultipleRegisters(unsigned char slaveID, unsigned char startAddress, unsigned char registersCount, unsigned short *holdingRegistersValues);
void ForceMultipleCoils(unsigned char slaveID, unsigned char coilAddress, unsigned char quantityOfCoils, unsigned short coilsData);
void ForceSingleCoil(unsigned char slaveID, unsigned char coilAddress, unsigned char forceCommand);
void ReadHoldingRegisters(unsigned char slaveID, unsigned char startingAddress, unsigned char holdingRegistersCount);
void ReadInputStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char inputsCount);
void ReadCoilStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char coilsCount);
void MBMaster(void);
int GetMBAnswer(unsigned char *Buffer);
int MBParseBuffer(unsigned char *Buffer, unsigned char *CommandArray, int bytesRead);

typedef struct MBCommandStructure{
    unsigned char slaveID;                              /* slaveID takes a values between 1 - 10 */
    
    unsigned char startAddressLO;                       /* startAddressLO is first address from which commands start. 
                                                        For Holding registers - 0 - 99
                                                        For Coils - 0 - 15
                                                        For Inputs - 0 - 15 */
    
    unsigned char numberOfHoldingRegisters;            /* numberOfHoldingRegisters is registers' count which must be written or read.
                                                       Values are between 1 - HOLDING_REGISTERS_NUMBER. 
                                                       For corectly initializing numberOfHoldingRegisters takes values between 1 and (HOLDING_REGISTERS_NUMBER - startAddressLO). */
    
    unsigned short *holdingRegistersValues;             /* This is pointer to values which must be written in Slave's registers. */
    
    unsigned char quantityOfCoils;                      /* This is coils' count which must be set or reset. */
    
    unsigned short coilsData;                           /* This is bit mask of coils where 1 - set, 0 - reset. 0000 1010 - set coil 1 and coil 3, reset the rest coils. */
    
    unsigned char forceCommand;                         /* forceCommand may be 0xFF or 0x00 respectivly for set or reset single coil. */
        
    unsigned char inputsCount;                          /* This is count of inputs which must be read - 1 - 16.
                                                        For corectly initializing inputsCount takes values between 1 and (INPUTS_NUMBER - startAddressLO).*/
    
}tModBusMasterCommand;

#endif
