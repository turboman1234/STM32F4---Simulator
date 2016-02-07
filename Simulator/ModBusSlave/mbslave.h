#ifndef _MBSLAVE_H
#define _MBSLAVE_H

#define PC_FLASH_HI	2
#define PC_FLASH_LO	3

// -------- Modbus Command Constants ------------------
#define DATA_START_ADDRESS_03		        		3

// -------- Modbus Address ranges ---------------------
#define HOLDING_REGISTERS_NUMBER        			100
#define COILS_NUMBER						200

// -------- Holding Registers constants ---------------
#define SCALE_ADDRESS				        	10
#define REMAINING_QUANTITY_ADDRESS		                12
#define	CONCRETE_QUANTITY_ADDRESS		                0
#define	CHEMICALS_QUANTITY_ADDRESS		                2

typedef unsigned char BOOL;

void MB_slave_transmit( void );
void MBPollSlave( void );
void ReceiveFSM( void );
void MBReceiveFSM( void );
void mb_slave_TimerExpired(void);
void slave_handle_request( void );
void MB_handle_request( void );
char process_cmd1(void);
char process_cmd3(void);
char process_cmd2(void);
char process_cmd5(void);
char process_cmd15(void);
char process_cmd16(void);

void InitNewMBSlaveDevices(void);
void ClearModBusSlaveMemory(unsigned char *pMemory, int size);
void CopyModBusMemory(unsigned char *source, unsigned char *destination, unsigned short cellsNumber);
BOOL MBSlaveAddressRecognition(unsigned char recieveAddress);


void MBTimerExpired(void);
void MBInit(void);

#define PACKET_SIZE		                                256
#define RESPONSE_SIZE 	                                        256

#define FALSE                                                   0
#define TRUE                                                    1

#define INVALID_SLAVE_INDEX                                     0xFFFFFFFF

#define INPUTS_NUMBER                                           16
#define OUTPUTS_NUMBER                                          16
#define MAX_MODBUS_SLAVE_DEVICES                                10

typedef struct Slave{
    unsigned char address;
    unsigned char inputs[INPUTS_NUMBER];
    unsigned char outputs[OUTPUTS_NUMBER];
    unsigned short holdingRegisters[HOLDING_REGISTERS_NUMBER];
    unsigned char responseBuffer[RESPONSE_SIZE];
    unsigned char recieveBuffer[PACKET_SIZE];
    BOOL isSlaveActive;
}ModBusSlaveUnit

#define IS_NEW_MB_SLAVE_DEVICE_CREATION_PERMITTED(deviceAddress, freeSlavesCount)    (((deviceAddress) >= 0) && ((deviceAddress) <= 255) && \
                                                                                      ((freeSlavesCount) > 0))


#endif
