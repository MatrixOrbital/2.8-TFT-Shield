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
#include <stdint.h>         // Find types like "uint8_t"
#include <stdbool.h>        // Find type "bool"
#include "font8x8_basic.h"
#include "ArduinoTFT28.h"   // Log
#include "ILI9341_SPI.h"
#include "ILI9341_HAL.h"

void HAL_ScreenInit(void)
{
  uint8_t ID[5];
  
  ILI9341_Reset();
  ILI9341_Init();
   
//ILI9341_ReadDisplayID(ID);
  ILI9341_ReadStatus(ID);
  Log("Status = 0x%02X%02X%02X%02X\n", ID[0], ID[1], ID[2], ID[3]);
}

void HAL_PutPixel(uint16_t x, uint16_t y, uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  uint16_t SixtyFiveK = 0;

  ILI9341_Select();   
  ILI9341_WriteCommand(0x2A);
  ILI9341_WriteData(x >> 8);
  ILI9341_WriteData(x & 0xFF);
  ILI9341_WriteData(x >> 8);
  ILI9341_WriteData(x & 0xFF);

  ILI9341_WriteCommand(0x2B);
  ILI9341_WriteData(y >> 8);
  ILI9341_WriteData(y & 0xFF);
  ILI9341_WriteData(y >> 8);
  ILI9341_WriteData(y & 0xFF);

  SixtyFiveK = (((uint16_t)Bdata) >> 3) | ((((uint16_t)Gdata) << 3) & 0x07E0) | ((((uint16_t)Rdata) << 8) & 0xf800);
  ILI9341_WriteCommand(0x2C);
  ILI9341_WriteData(SixtyFiveK >> 8); // send top byte first since endianness is reversed
  ILI9341_WriteData(SixtyFiveK);      // send lower byte second since endianness is reversed
  ILI9341_Deselect();         
}

void HAL_DrawChar(uint16_t x, uint16_t y, uint8_t charData)
{
  uint16_t SixtyFiveK = 0;
  uint8_t* addr;
  charData &= 0x7F; // makes sure that charData is < 128
  addr = &(font8x8_basic[charData][0]);
  uint8_t data;  
  uint16_t mult = 0;

  // this draws the font8x8_basic blown twice in width and height
  for (int i =0; i <8; i++)
  {
    data = *addr;
    for (int k =0; k <2; k++)
    {
      mult = 0;
      for (int j =0; j <8; j++)
      {       
        ILI9341_Select();   
        ILI9341_WriteCommand(0x2A);
        ILI9341_WriteData((x+mult) >> 8);
        ILI9341_WriteData((x+mult) & 0xFF);
        ILI9341_WriteData((x+1+mult) >> 8);
        ILI9341_WriteData((x+1+mult) & 0xFF);
      
        ILI9341_WriteCommand(0x2B);
        ILI9341_WriteData((y+k) >> 8);
        ILI9341_WriteData((y+k) & 0xFF);
        ILI9341_WriteData((y+k) >> 8);
        ILI9341_WriteData((y+k) & 0xFF);
      
        // RGB can be inserted here in the future
        if (data & (1 << j))
        {
          SixtyFiveK = (((uint16_t)0xFF) >> 3) | ((((uint16_t)0xFF) << 3) & 0x07E0) | ((((uint16_t)0xFF) << 8) & 0xf800);                  
        }        
        else 
        {
          SixtyFiveK = (((uint16_t)0x00) >> 3) | ((((uint16_t)0x00) << 3) & 0x07E0) | ((((uint16_t)0x00) << 8) & 0xf800);          
        } 
        
        ILI9341_WriteCommand(0x2C);
        ILI9341_WriteData(SixtyFiveK >> 8); // send top byte first since endianness is reversed
        ILI9341_WriteData(SixtyFiveK);      // send lower byte second since endianness is reversed
        ILI9341_WriteData(SixtyFiveK >> 8); // send top byte first since endianness is reversed
        ILI9341_WriteData(SixtyFiveK);      // send lower byte second since endianness is reversed
        ILI9341_Deselect();  
        mult = 2*(j+1);      
      }
    }
    y+=2;
    *addr++;
  }      
}

void HAL_ScreenFill(uint8_t R, uint8_t G, uint8_t B)
{
  uint16_t column, row;

  for (column = 0; column < 240; column++)
    for (row = 0; row < 320; row++)
      HAL_PutPixel(column, row, R, G, B);
}

void HAL_ScreenWipe(uint8_t R, uint8_t G, uint8_t B)
{
  uint16_t column, row;
  uint8_t byte1, byte2;

  byte1 = (R & 0xf8) + ((G >> 5) & 0x07);         //Can be simplified
  byte2 = ((G << 5) & 0xe0) + ((B >> 3) & 0x1f);  //Can be simplified

  ILI9341_Select();   
  ILI9341_WriteCommand(0x2A); 
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0xEF);

  ILI9341_WriteCommand(0x2B);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x01);
  ILI9341_WriteData(0x3F);

  ILI9341_WriteCommand(0x2C);
  ILI9341_WriteData(byte1);
  ILI9341_WriteData(byte2);

//  i8080_Write(0x3C, I8080COMMAND); // Continue write
  for (column = 0; column < 240; column++)
  {
    for (row = 0; row < 320; row++)
    {
      ILI9341_WriteData(byte1);
      ILI9341_WriteData(byte2);
    }
  }
}


void HAL_BoxWH(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint8_t R, uint8_t G, uint8_t B)
{
  // Bounds checking
  if (x1 + w > DISPLAY_PWIDTH) w = (DISPLAY_PWIDTH) - x1;
  if (y1 + h > DISPLAY_PHEIGHT) h = DISPLAY_PHEIGHT - y1;
  if (x1 > DISPLAY_PWIDTH - 1) return;
  if (y1 > DISPLAY_PHEIGHT - 1) return;
    
  uint16_t SixtyFiveK;
  
  ILI9341_Select();   
  ILI9341_WriteCommand(0x2A);
  ILI9341_WriteData(x1 >> 8);
  ILI9341_WriteData(x1 & 0xFF);
  ILI9341_WriteData((x1+w-1) >> 8);
  ILI9341_WriteData((x1+w-1) & 0xFF);

  ILI9341_WriteCommand(0x2B);
  ILI9341_WriteData(y1 >> 8);
  ILI9341_WriteData(y1 & 0xFF);
  ILI9341_WriteData((y1+h-1) >> 8);
  ILI9341_WriteData((y1+h-1) & 0xFF);

  SixtyFiveK = (((uint16_t)B) >> 3) | ((((uint16_t)G) << 3) & 0x07E0) | ((((uint16_t)R) << 8) & 0xf800);
  ILI9341_WriteCommand(0x2C); 
  for (int j = 0; j < h; j++)
  {   
    for (int i = 0; i < w; i++)
    {
      ILI9341_WriteData(SixtyFiveK >> 8); // send top byte first since endianness is reversed
      ILI9341_WriteData(SixtyFiveK);      // send lower byte second since endianness is reversed
    }
  }
  ILI9341_Deselect();         

}
