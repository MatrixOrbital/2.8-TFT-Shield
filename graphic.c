/* Graphic.c - The top level graphic primitives functions for COLOUR TFT displays. */
 
#include <stdint.h>       // Find types like "uint8_t"
#include <stdbool.h>      // Find type "bool"
#include "ILI9341_HAL.h"
#include "ArduinoTFT28.h"
#include "graphic.h"

// PUBLIC
color_type gCurColour;

// PRIVATE
uint8_t gCurrentY, gCurrentX;
uint8_t gMaxAscii, MinAscii;
uint8_t gxStart, yStart;
uint8_t gxSpacing, ySpacing;
uint8_t gxFontSize, yFontSize;
uint8_t gScrollLimit;
uint8_t gCurrentFont;

void displayChar(uint16_t x, uint16_t y, uint8_t data)
{
  HAL_DrawChar(x, y, data);  
  return;
}

void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, color_type Colour)
{
  int16_t dyabs;
  int16_t sdy;
  uint8_t dxabs;
  int16_t Err;
  uint16_t px, py;
  uint8_t i;
  int16_t temp;

  if (y1 == y2)
    hline(x1, x2, y2, Colour);
  else {	// for all other cases, which is the old way
    // Flip things if neccessary
    if (x1 > x2) {
      temp = y1;
      y1 = y2;
      y2 = temp;
      temp = x1;
      x1 = x2;
      x2 = temp;
    }

    // Calculate the sign
    if ((dyabs = y2 - y1) < 0) {
      sdy = -1;
      dyabs = -dyabs;
    } else {
      sdy = 1;
    }

    dxabs  = x2 - x1;
	
		Err = 0;
    px = x1;
		py = y1;

    HAL_PutPixel(px, py, Colour.Red, Colour.Green, Colour.Blue);

		if (dxabs > dyabs) {
			for (i = dxabs; i; i--) {
				Err += dyabs;
				if ((Err << 1) >= dxabs)	{
					Err -= dxabs;
					py += sdy;
				}
        px++;
				HAL_PutPixel(px, py, Colour.Red, Colour.Green, Colour.Blue);
			}
		}	else {
			for (i = dyabs; i; i--) {
				Err += dxabs;
				if ((Err << 1) >= dyabs)	{
					Err -= dyabs;
					px++;
				}
				py += sdy;
				HAL_PutPixel(px, py, Colour.Red, Colour.Green, Colour.Blue);
			}
		}
	}
}

void hline(int16_t x1, int16_t x2, int16_t y, color_type Colour)
{  
  // check if the horizontal line is within the viewing area
  if ((y >= 0) && (y < DISPLAY_PHEIGHT))
    box(x1, y, x2, y, Colour);   
}

void box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, color_type Colour)
{
  int16_t width;
  int16_t height;
  int16_t temp;

  if (x1 > x2) {
    temp = x1;
  	 x1 = x2;
    x2 = temp;
  }

  if (y1 > y2) {
    temp = y1;
  	 y1 = y2;
    y2 = temp;
  }

  // check values first
  if (x1 < 0) x1 = 0;
  if (y1 < 0) y1 = 0;

  width = x2 - x1 + 1;
  height = y2 - y1 + 1;

  boxwh(x1, y1, width, height, Colour);  
}

void boxwh(int16_t x1, int16_t y1, uint16_t w, uint16_t h, color_type Colour)
{
  HAL_BoxWH(x1, y1, w, h, Colour.Red, Colour.Green, Colour.Blue);
}

void filledrect(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd, color_type Colour)
{
  box(XStart, YStart, XEnd, YEnd, Colour);
}


void rect(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd, color_type Colour)
{
	hline(XStart, XEnd, YEnd, Colour);					// bottom horizontal
	hline(XStart, XEnd, YStart, Colour);				// top horizontal
  line(XStart, YStart, XStart, YEnd, Colour);// left vertical
	line(XEnd, YEnd, XEnd, YStart, Colour);		// right vertical
}

void ClearScreen(uint8_t R, uint8_t G, uint8_t B)
{
  HAL_ScreenWipe(R, G, B);
}
