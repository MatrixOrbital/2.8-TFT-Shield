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

void HAL_BlockTest(void)
{
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
  for (int i = 0; i < 255; i++)
  {
    ILI9341_WriteData(0x00);
    ILI9341_WriteData(0x00);
  }
  ILI9341_Deselect();   
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
  uint16_t multy = 0;

  // this draws the font8x8_basic blown twice in width and height
  for (int i =0; i <8; i++)
  {
    data = *addr;
    multy = 0;
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
      multy = (k+1);
    }
    y+=2;
    *addr++;
  }      
}

/***********************************************************************************************************
** HAL_PutSmallBitmap()
** This function takes care of placing bitmaps with a maximum data size of MAX_SMALL_BITMAP_DATA_SIZE which
** is defined in graphic.h and is largely dependant on the convenient availibility of memory.  If a huge
** amount of memory comes available, this function is the preferred way to deal with any bimap.  Currently,
** it is a relatively large character of 10x16 pixels.
**
** Conversation: Obviously it would be more direct to tear through the black and white 8 pixels per byte
** style bitmap as stored in a GLK and simply replace black with three bytes of FFh and white with zeroes.
** Instead, due to the fact that I am trying to keep the concept of Hardware Abstraction Layer active, I am
** using memory by pre-stuffing the huge array.  This is in prep of actual colour when I get to it and I
** will still want to differentiate between small enough to pre-stuff and so big I have to do it state-wise.
** I am probably too optimistic about the possibility of finding the memory (and other resources), but if it
** becomes necessary to optimize memory usage, you can rip and replace this easier at this level than if it
** were up a level.
***********************************************************************************************************/
void HAL_PutSmallBitmap (uint16_t x, uint16_t y, uint8_t w, uint8_t h, uint8_t *Data)
{
	uint16_t xpos, ypos;
  uint8_t index = 0;
	
  ILI9341_WriteCommand(0x2A); 				// Set column Command
  ILI9341_WriteData((x >> 8) & 0xFF);	// Start column high byte
  ILI9341_WriteData(x);								// Start column low byte
  x += w;															// Calculate end column
  ILI9341_WriteData((x >> 8) & 0xFF);	// End column high byte
  ILI9341_WriteData(x);								// End column low byte

  ILI9341_WriteCommand(0x2B);					// Set Page command (Page is ILI-speak for "row" because sub-pixels)
  ILI9341_WriteData((y >> 8) & 0xFF); // Start page high byte
  ILI9341_WriteData(y & 0xFF);				// Start page low byte
  y += h;															// Calculate end page.
  ILI9341_WriteData((y >> 8) & 0xFF);	// End page high byte
  ILI9341_WriteData(y & 0xFF);				// End page low byte
	
  ILI9341_WriteCommand(0x2C); 				// Write Command - indeterminate quantity of data follows
	
	for (ypos=0; ypos<h; ypos++)
	{
		for (xpos=0; xpos<w; xpos++)
		{
			// write three bytes of colour pixel data (one pixel)
  		ILI9341_WriteData(Data[index++]);	// Red
  		ILI9341_WriteData(Data[index++]);	// Green
  		ILI9341_WriteData(Data[index++]);	// Blue
		}
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

void HAL_BitmapTest(void)
{
  uint8_t StatusData[4];
  uint8_t IdData[3];
  uint8_t DisplayPowerMode, DisplayMADCTL, DisplayImageMode, DisplaySignalMode;
  uint8_t temp;

  ILI9341_ReadStatus(StatusData);
  temp = StatusData[0];
  temp = StatusData[1];
  temp = StatusData[2];
  temp = StatusData[3];

  ILI9341_ReadDisplayID(IdData);
  temp = IdData[0];
  temp = IdData[1];
  temp = IdData[2];

  ILI9341_ReadDisplayPowerMode(&DisplayPowerMode);    // 0x9C is normal
  temp = DisplayPowerMode;

  ILI9341_ReadDisplayMADCTL(&DisplayMADCTL);
  temp = DisplayMADCTL;

  ILI9341_ReadDisplayImageMode(&DisplayImageMode);
  temp = DisplayImageMode;

  ILI9341_ReadDisplaySignalMode(&DisplaySignalMode);
  temp = DisplaySignalMode;

  ILI9341_WriteCommand(0x2A); 	// Set column Command
  ILI9341_WriteData(0);	        // Start column high byte
  ILI9341_WriteData(0);				  // Start column low byte
  ILI9341_WriteData(0);	        // End column high byte
  ILI9341_WriteData(239);				// End column low byte

  ILI9341_WriteCommand(0x2B);		// Set Page command (Page is ILI-speak for "row" because sub-pixels)
  ILI9341_WriteData(0);         // Start page high byte
  ILI9341_WriteData(0);			    // Start page low byte
  ILI9341_WriteData(0x01);	    // End page high byte
  ILI9341_WriteData(0x3F);			// End page low byte

  ILI9341_WriteCommand(0x2C); 	// Write Command - indeterminate quantity of data follows
  for (int y = 0; y < 320; y++) {
    for (int x = 0; x < 240; x++) {
      if (y > 279)      ILI9341_WriteData16(COLOR_WHITE);
      else if (y > 239) ILI9341_WriteData16(COLOR_YELLOW);
      else if (y > 199) ILI9341_WriteData16(COLOR_MAGENTA);
      else if (y > 159) ILI9341_WriteData16(COLOR_CYAN);
      else if (y > 119) ILI9341_WriteData16(COLOR_GREEN);
      else if (y > 79)  ILI9341_WriteData16(COLOR_RED);
      else if (y > 39)  ILI9341_WriteData16(COLOR_BLUE);
      else              ILI9341_WriteData16(COLOR_BLACK);
    }
  }
return;

}

void HAL_BitmapInitialize(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  ILI9341_WriteCommand(0x2A); 				// Set column Command
  ILI9341_WriteData(x >> 8);	        // Start column high byte
  ILI9341_WriteData(x & 0xFF);				// Start column low byte
  x += w;															// Calculate end column
  ILI9341_WriteData(x >> 8);	        // End column high byte
  ILI9341_WriteData(x & 0xFF);				// End column low byte

  ILI9341_WriteCommand(0x2B);					// Set Page command (Page is ILI-speak for "row" because sub-pixels)
  ILI9341_WriteData(y >> 8);          // Start page high byte
  ILI9341_WriteData(y & 0xFF);				// Start page low byte
  y += h;															// Calculate end page.
  ILI9341_WriteData(y >> 8);	        // End page high byte
  ILI9341_WriteData(y & 0xFF);				// End page low byte

  ILI9341_WriteCommand(0x2C); 				// Write Command - indeterminate quantity of data follows
}

void HAL_BitmapPutData(uint8_t Data)
{
  uint16_t SixtyFiveK = 0;

  SixtyFiveK = (((uint16_t)Data) >> 3) | ((((uint16_t)Data) << 3) & 0x07E0) | ((((uint16_t)Data) << 8) & 0xf800);
  ILI9341_WriteData(SixtyFiveK);      // send lower byte first since little endianness is set
  ILI9341_WriteData(SixtyFiveK >> 8); // send top byte second since little endianness is set
}
