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
#include "ArduinoTFT28.h"
#include "ILI9341_SPI.h"

void ILI9341_Init(void)
{
  Log("ILI\n");
  
  ILI9341_Select();
  ILI9341_WriteCommand(ICMD_SWRESET); // Software reset
  ILI9341_Deselect();
  MyDelay(100);
  MyDelay(100);

  ILI9341_Select();
  ILI9341_WriteCommand(ICMD_PIXELFORMAT); 
  ILI9341_WriteData(IPRM_PIXELFORMAT16);  
  ILI9341_Deselect();        
  MyDelay(10);
  
  ILI9341_Select();
  ILI9341_WriteCommand(0xED); //
  ILI9341_WriteData(0x64);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x12);
  ILI9341_WriteData(0x81);
  ILI9341_Deselect();        
  MyDelay(10);
  

  ILI9341_Select();    
  ILI9341_WriteCommand(0xE8); //
  ILI9341_WriteData(0x85);  //
  ILI9341_WriteData(0x11);  //
  ILI9341_WriteData(0x78);  //
  ILI9341_Deselect();         
  MyDelay(10);

  ILI9341_Select();    
  ILI9341_WriteCommand(0xCB); //
  ILI9341_WriteData(0x39);  //
  ILI9341_WriteData(0x2C);  //
  ILI9341_WriteData(0x00);  //
  ILI9341_WriteData(0x33);  //
  ILI9341_WriteData(0x02);  //
  ILI9341_Deselect();         
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xF7); //
  ILI9341_WriteData(0x20);  //
  ILI9341_Deselect();         
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xEA); //
  ILI9341_WriteData(0x00);  //
  ILI9341_WriteData(0x00);  //
  ILI9341_Deselect();         
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0x36); //
  ILI9341_WriteData(0x08);  //
  ILI9341_Deselect();         
  MyDelay(10);

  ILI9341_Select();   
  ILI9341_WriteCommand(0xF6);
  ILI9341_WriteData(0x01);//0x01 
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);//<<- RGB INTERFACE
  ILI9341_Deselect();      
  MyDelay(10); 
   

  ILI9341_Select();    
  ILI9341_WriteCommand(0xB1); //
  ILI9341_WriteData(0x00);  //
  ILI9341_WriteData(0x16);  //
  ILI9341_Deselect();          
  MyDelay(10);

  ILI9341_Select();    
  ILI9341_WriteCommand(0xB6); //
  ILI9341_WriteData(0x0A);  //
  ILI9341_WriteData(0xA2);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xF2); //
  ILI9341_WriteData(0x02);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xE0); //
  ILI9341_WriteData(0x0F);  //
  ILI9341_WriteData(0x22);  //
  ILI9341_WriteData(0x21);  //
  ILI9341_WriteData(0x0C);  //
  ILI9341_WriteData(0x0F);  //
  ILI9341_WriteData(0x09);  //
  ILI9341_WriteData(0x4A);  //
  ILI9341_WriteData(0x98);  //
  ILI9341_WriteData(0x37);  //
  ILI9341_WriteData(0x05);  //
  ILI9341_WriteData(0x0C);  //
  ILI9341_WriteData(0x00);  //
  ILI9341_WriteData(0x15);  //
  ILI9341_WriteData(0x16);  //
  ILI9341_WriteData(0x0F);  //
  ILI9341_Deselect();          
  MyDelay(10);
  

  ILI9341_Select();    
  ILI9341_WriteCommand(0xE1); //
  ILI9341_WriteData(0x00);  //
  ILI9341_WriteData(0x17);  //
  ILI9341_WriteData(0x18);  //
  ILI9341_WriteData(0x04);  //
  ILI9341_WriteData(0x0F);  //
  ILI9341_WriteData(0x06);  //
  ILI9341_WriteData(0x2E);  //
  ILI9341_WriteData(0x35);  //
  ILI9341_WriteData(0x44);  //
  ILI9341_WriteData(0x07);  //
  ILI9341_WriteData(0x11);  //
  ILI9341_WriteData(0x0E);  //
  ILI9341_WriteData(0x29);  //
  ILI9341_WriteData(0x2C);  //
  ILI9341_WriteData(0x00);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xC7); //
  ILI9341_WriteData(0xAF);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xCF); //
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x99);
  ILI9341_WriteData(0x30);
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xC1); //
  ILI9341_WriteData(0x12);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xC0); //
  ILI9341_WriteData(0x21);  //
  ILI9341_Deselect();          
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xC5); //
  ILI9341_WriteData(0x40);  //
  ILI9341_WriteData(0x20);  //
  ILI9341_Deselect();            
  MyDelay(10);
  
  ILI9341_Select();    
  ILI9341_WriteCommand(0xB4); //
  ILI9341_WriteData(0x06);  //
  ILI9341_Deselect();         

  ILI9341_Select();    
  ILI9341_WriteCommand(0xB0);      //Command  "Set Gamma Negative"
  ILI9341_WriteData(0xC0);     //Parameter '0x00"
  ILI9341_Deselect();      
   
  ILI9341_Select();    
  ILI9341_WriteCommand(0x11); //
  ILI9341_Deselect();         
  MyDelay(120);

  ILI9341_Select();    
  ILI9341_WriteCommand(0x29); //Set_display_on  
  ILI9341_Deselect();         
  MyDelay(120);
}

void ILI9341_Reset(void)  // hardware reset
{
  ILI9341_RST_HI;            // set reset high (not reset state)
  MyDelay(10);               // for 10 ms
  ILI9341_RST_LO;            // set reset low (reset state)
  MyDelay(10);               // for 10 ms
  ILI9341_RST_HI;            // set reset high (not reset state)
  MyDelay(150);              // for 150 ms
}

inline void ILI9341_Deselect(void)
{
  SetPin(ILI9341_CS_PIN, 1);
}

inline void ILI9341_Select(void)
{
  SetPin(ILI9341_CS_PIN, 0);
}

void ILI9341_WriteCommand(uint8_t Command) // Write a single byte command
{
  // CS enabale/disable is done prior/after to calling this function
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(Command);            // Transmit the command  
}

void ILI9341_WriteData(uint8_t Data) // Write a single byte command
{
  // CS enabale/disable is done prior/after to calling this function
  SetPin(ILI9341_DC_PIN, 1);     // Indicate DATA
  SPI_Write(Data);               // Transmit the data
  
}

void ILI9341_Write1Data(uint8_t Command, uint8_t Data1) // Write a single data byte parameter
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(Command);            // Transmit the command
  SetPin(ILI9341_DC_PIN, 1);     // Indicate DATA
  SPI_Write(Data1);              // Transmit the data
  ILI9341_Deselect();
}

void ILI9341_Write2Data(uint8_t Command, uint8_t Data1, uint8_t Data2) // Writes two bytes of data
{
  ILI9341_Select();
   SetPin(ILI9341_DC_PIN, 0);    // Indicate COMMAND
  SPI_Write(Command);            // Transmit the command
  SetPin(ILI9341_DC_PIN, 1);     // Indicate DATA
  SPI_Write(Data1);              // Transmit the data
  SPI_Write(Data2);              // Transmit the data
  ILI9341_Deselect();
}

void ILI9341_Write3Data(uint8_t Command, uint8_t Data1, uint8_t Data2, uint8_t Data3) // Writes three bytes of data
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(Command);            // Transmit the command
  SetPin(ILI9341_DC_PIN, 1);     // Indicate DATA
  SPI_Write(Data1);              // Transmit the data
  SPI_Write(Data2);              // Transmit the data
  SPI_Write(Data3);              // Transmit the data
  ILI9341_Deselect();
}

void ILI9341_WriteData16(uint16_t Data)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 1);                    // Indicate Data
  SPI_Write((uint8_t)(Data & 0xFF));              // Transmit the low byte
  SPI_Write((uint8_t)((Data >> 8) & 0xFF));       // Transmit the high byte
  ILI9341_Deselect();
}

void ILI9341_ContinueWrite(uint16_t ColorData)
{
  uint8_t temp = (ColorData & 0xFF);

  ILI9341_WriteCommand(0x3C);

  ILI9341_WriteData(temp);
  temp = ((ColorData >> 8) & 0xFF);
  ILI9341_WriteData(temp);
}

void ILI9341_ReadStatus(uint8_t *Parms)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(0x09);               // Transmit the command
  Parms[0] = SPI_Read(); // Throw away
  Parms[0] = SPI_Read();
  Parms[1] = SPI_Read();
  Parms[2] = SPI_Read();
  Parms[3] = SPI_Read();
  ILI9341_Deselect();
}

void ILI9341_ReadDisplayID(uint8_t *Parms)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(0x04);               // Transmit the command
  Parms[0] = SPI_Read();         // Throw away
  Parms[0] = SPI_Read();
  Parms[1] = SPI_Read();
  Parms[2] = SPI_Read();
  ILI9341_Deselect();
}

void ILI9341_ReadDisplayPowerMode(uint8_t *Parm)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(0x0A);               // Transmit the command
  *Parm = SPI_Read();            // Throw away
  *Parm = SPI_Read();
  ILI9341_Deselect();
}

void ILI9341_ReadDisplayMADCTL(uint8_t *Parm)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(0x0B);               // Transmit the command
  *Parm = SPI_Read();            // Throw away
  *Parm = SPI_Read();
  ILI9341_Deselect();
}

//                                                           THIS FUNCTION THE SAME AS THE NEXT ONE
void ILI9341_ReadDisplayImageMode(uint8_t *Parm)
{
  ILI9341_Select();
  SetPin(ILI9341_DC_PIN, 0);     // Indicate COMMAND
  SPI_Write(0x0D);               // Transmit the command
  *Parm = SPI_Read();            // Throw away
  *Parm = SPI_Read();
  ILI9341_Deselect();
}

void ILI9341_ColorSet(void)
{
  uint8_t Counter;

  ILI9341_WriteCommand(0xE1);
  
  for(Counter = 0; Counter < 0x20; Counter++)
    ILI9341_WriteData(Counter << 1);

  for(Counter = 0; Counter < 0x40; Counter++)
    ILI9341_WriteData(Counter);

  for(Counter = 0; Counter < 0x20; Counter++)
    ILI9341_WriteData(Counter << 1);
}
