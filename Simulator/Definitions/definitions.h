//Buttons' definitions
#define BUTTON_1        1
#define BUTTON_2        2
#define BUTTON_3        3
#define BUTTON_4        4
#define BUTTON_5        5
#define BUTTON_6        6
#define BUTTON_7        7
#define BUTTON_8        8

//LED's definitions
#define LED_1           9
#define LED_2           10
#define LED_3           11
#define LED_4           12
#define LED_5           13
#define LED_6           14
#define LED_7           15
#define LED_8           16

//Tirmers' definitions
#define TRIMMER_1       17
#define TRIMMER_2       18
#define TRIMMER_3       19

//Switches' definitions
#define SWITCH_1        20
#define SWITCH_2        21

//Inputs' definitions
#define INPUT_1                 22
#define INPUT_2                 23
#define INPUT_3                 24
#define INPUT_4                 25
#define INPUT_5                 26
#define INPUT_6                 27
#define INPUT_7                 28
#define INPUT_8                 29
#define INPUT_9                 30
#define INPUT_10                31
#define INPUT_11                32
#define INPUT_12                33
#define INPUT_13                34
#define INPUT_14                35
#define INPUT_15                36
#define INPUT_16                37

//Outputs' definitions
#define OUTPUT_1                38
#define OUTPUT_2                39
#define OUTPUT_3                40
#define OUTPUT_4                41
#define OUTPUT_5                42
#define OUTPUT_6                43
#define OUTPUT_7                44
#define OUTPUT_8                45
#define OUTPUT_9                46
#define OUTPUT_10               47
#define OUTPUT_11               48
#define OUTPUT_12               49
#define OUTPUT_13               50
#define OUTPUT_14               51
#define OUTPUT_15               52
#define OUTPUT_16               53

//ADC
#define ADC_1                   54
#define ADC_2                   55

//DAC
#define DAC_1                   56
#define DAC_2                   57

//TIMERS
#define TIMER_1                 58
#define TIMER_2                 59
#define TIMER_3                 60
#define TIMER_4                 61
#define TIMER_5                 62
#define TIMER_6                 63
#define TIMER_7                 64
#define TIMER_8                 65
#define TIMER_9                 66
#define TIMER_10                67
#define TIMER_11                68
#define TIMER_12                69
#define TIMER_13                70
#define TIMER_14                71
#define TIMER_15                72
#define TIMER_16                73
#define TIMER_COMMUNICATION     74

//UART2
#define USART_2                 75
#define USART_3                 76        

//Macros for digital IO, switches, LEDs
#define ON                      1
#define OFF                     0

//Macros for buttons
#define PRESSED                 1
#define NOT_PRESSED             0

//Macros for timers
#define ELAPSED                 1
#define NOT_ELAPSED             0

//Macros for analog value (12 bits)
#define MIN_ANALOG_VALUE_12b    0
#define MAX_ANALOG_VALUE_12b   4095

//Macros for analog value (10 bits)
#define MIN_ANALOG_VALUE_10b    0
#define MAX_ANALOG_VALUE_10b    1023

//Macros for analog value (8 bits)
#define MIN_ANALOG_VALUE_8b     0
#define MAX_ANALOG_VALUE_8b     255

#define T_10_MS		10
#define T_100_MS	100
#define T_1_S		1000

#define IS_OUTPUT_STATE_VALID (STATE)          (((STATE) == ON) || \
                                                ((STATE) == OFF))

#define IS_TIMER_ID_VALID (TIMER_ID)           (((TIMER_ID) == TIMER_1)   || \
                                                ((TIMER_ID) == TIMER_2)   || \
                                                ((TIMER_ID) == TIMER_3)   || \
                                                ((TIMER_ID) == TIMER_4)   || \
                                                ((TIMER_ID) == TIMER_5)   || \
                                                ((TIMER_ID) == TIMER_6)   || \
                                                ((TIMER_ID) == TIMER_7)   || \
                                                ((TIMER_ID) == TIMER_8)   || \
                                                ((TIMER_ID) == TIMER_9)   || \
                                                ((TIMER_ID) == TIMER_10)  || \
                                                ((TIMER_ID) == TIMER_11)  || \
                                                ((TIMER_ID) == TIMER_12)  || \
                                                ((TIMER_ID) == TIMER_13)  || \
                                                ((TIMER_ID) == TIMER_14)  || \
                                                ((TIMER_ID) == TIMER_15)  || \
                                                ((TIMER_ID) == TIMER_16)  || \
                                                ((TIMER_ID) == TIMER_COMMUNICATION)

#define IS_USART_ID_VALID (usartID)             (((usartID) == USART_2) || \
                                                 ((usartID) == USART_3))
