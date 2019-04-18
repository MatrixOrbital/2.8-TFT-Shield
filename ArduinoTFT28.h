#ifndef __ARDUINOTFT28_H
#define __ARDUINOTFT28_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>              // Find integer types like "uint8_t"  
#include <stdbool.h>             // Find type "bool"
#include <stdio.h>               // sprintf()

// defines related to hardware and relevant only to the hardware abstraction layer (this and .ino files)
#define GPIO_0                      0 // PD0 - D0
#define GPIO_1                      1 // PD1 - D1
#define GPIO_2                      2 // PD2 - D2
#define GPIO_3                      3 // PD3 - D3
#define GPIO_4                      4 // PD4 - D4
#define GPIO_5                      5 // PD5 - D5
#define GPIO_6                      6 // PD6 - D6
#define GPIO_7                      7 // PD7 - D7
#define GPIO_8                      8 // PB0 - D8
#define GPIO_9                      9 // PB1 - D9
#define SlaveSelect_PIN            10 // PB2 - D10
#define MOSI_PIN                   11 // PB3 - D11
#define MISO_PIN                   12 // PB4 - D12
#define SCLK_PIN                   13 // PB5 - D13
//#define GPIO_14                  14 // PA0 - D14
#define GPIO_15                    15 // PA0 - not sure why this starts at 15 instead of 14
#define GPIO_16                    16 // PA1 
#define GPIO_17                    17 // PA2 
#define GPIO_18                    18 // PA3 
#define GPIO_19                    19 // PA4 


// Redefined Arduino parameters for access outside .ino
#define  PIN_INPUT                 INPUT                 // Input Floating Mode
#define  PIN_OUTPUT                OUTPUT                // Output Push Pull Mode

#define SPISpeed            10000000
#define WorkBuffSz 64UL

// Defines related to the device
#define PROGRAMCODE             0x99
#define CODEVERSION             0x66

// Defines related to Pi link
#define CMDPREFIX               0xFE

// Pi Host Command Codes
#define GET_MESSAGE             0x0C
#define SET_CELEBRATE           0x0F
#define GET_ADC0_VAL            0x10
#define GET_ADC1_VAL            0x11
#define GET_ADC2_VAL            0x12
#define GET_ADC3_VAL            0x13
#define GET_ADC4_VAL            0x14
#define GET_ADC5_VAL            0x15
#define GET_ADC6_VAL            0x16
#define GET_ADC7_VAL            0x17
#define GET_ADC_STAT            0x20
#define GET_OWTP0_VAL           0x30
#define GET_OWTP1_VAL           0x31
#define GET_OWTP_STAT           0x40

// Command States
#define PI_IDLE                 0x11
#define PI_COMMAND_START        0x22
#define PI_COMMAND              0x33

#define COMM_BUF_SIZE             64
#define MAX_RET_MSG_SIZE          63

#define USE_SERIAL_DEBUG                // Uncomment to activate serial output debugging
#ifdef USE_SERIAL_DEBUG
extern char LogBuf[WorkBuffSz]; 
#define Log(...)  { sprintf(LogBuf,__VA_ARGS__); DebugPrint(LogBuf); } // Stuff string and parms via sprintf and output
#else
#define Log(...)
#endif

// Global Variables

// Function Prototypes
//void MainLoop(void);

// Hardware peripheral abstraction function prototypes
void InitPin(uint8_t, uint8_t);
uint8_t ReadPin(uint8_t);
void SetPin(uint8_t, bool);
//void SPI_Enable(void);
//void SPI_Disable(void);
void SPI_Write(uint8_t data);
//void SPI_WriteByte(uint8_t data);
//void SPI_WriteBuffer(uint8_t *Buffer, uint32_t Length);
uint8_t SPI_Read(void);
uint8_t SPI_RW(uint8_t data);
void SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length);

// These functions encapsulate Arduino library functions
void DebugPrint(char *str);
void MyDelay(uint32_t DLY);
uint32_t MyMillis(void);
void DisableInt(void);
void EnableInt(void);

void DrawSquares(void);


#ifdef __cplusplus
}
#endif

#endif
