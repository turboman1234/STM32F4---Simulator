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
void ReadInputStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char coil);
void ReadCoilStatus(unsigned char slaveID, unsigned char startingAddress, unsigned char coilsCount);
void MBMaster(void);
int GetMBAnswer(unsigned char *Buffer);
int MBParseBuffer(unsigned char *Buffer, unsigned char *CommandArray, int bytesRead);


#endif
