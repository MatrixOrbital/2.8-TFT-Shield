/*
 * 
 *   Copyright (c) 2019 Matrix Orbital, Corp. https://www.matrixorbital.com/
 *   
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *   
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *   
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 *   
*/
#ifndef __ILI9341SPI_H
#define __ILI9341SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#define ILI9341_RST_PIN   GPIO_4  // TFT Reset line - active low
#define ILI9341_CS_PIN    GPIO_7  // TFT Chip Select line - active low
#define ILI9341_DC_PIN    GPIO_3  // TFT Data/Command line - high for data, low for command

#define ILI9341_RST_LO    SetPin(ILI9341_RST_PIN, 0)
#define ILI9341_RST_HI    SetPin(ILI9341_RST_PIN, 1)

// ILI9341 Command Codes - ICMD = ILI Commands - IPRM = ILI Parameters
#define ICMD_SWRESET               0x01  // Software Reset
#define ICMD_PIXELFORMAT           0x3A  // 
#define IPRM_PIXELFORMAT16         0x55  // 16 bits per pixel
#define IPRM_PIXELFORMAT18         0x66  // 18 bits per pixel

void ILI9341_Init(void);
void ILI9341_WriteCommand(uint8_t);     // Write a single byte command
void ILI9341_WriteData(uint8_t);        // Writes one byte of data
void ILI9341_WriteData16(uint16_t);
void ILI9341_Write1Data(uint8_t Command, uint8_t Data1); // Write a single data byte parameter
void ILI9341_Write2Data(uint8_t Command, uint8_t Data1, uint8_t Data2); // Writes two bytes of data
void ILI9341_Write3Data(uint8_t Command, uint8_t Data1, uint8_t Data2, uint8_t Data3); // Writes three bytes of data
void ILI9341_Reset(void);
void ILI9341_Deselect(void);
void ILI9341_Select(void);
void ILI9341_ContinueWrite(uint16_t);
void ILI9341_ReadStatus(uint8_t *);
void ILI9341_ReadDisplayID(uint8_t *);
void ILI9341_ReadDisplayPowerMode(uint8_t *);
void ILI9341_ReadDisplayMADCTL(uint8_t *);
void ILI9341_ReadDisplayImageMode(uint8_t *);
void ILI9341_ColorSet(void);

#ifdef __cplusplus
}
#endif

#endif
