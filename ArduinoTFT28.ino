#include <arduino.h>       
#include <stdint.h>       // Find types like "uint8_t"
#include <stdbool.h>      // Find type "bool"
#include <SPI.h>          // Arduino SPI library
#include "ILI9341_HAL.h"
#include "graphic.h"
#include "calibrate.h"
#include "touch.h"
#include "ArduinoTFT28.h"


color_type LineColor, BlankingColor;
uint64_t Time2Draw = 0;
uint64_t Time2ReadTouch = 0;
char LogBuf[WorkBuffSz];
int16_t SS_x1, SS_y1, SS_x2, SS_y2, dx1, dy1, dx2, dy2, stride;
uint16_t ChangeInterval = 0;
bool RandomLines = false;
bool greenTouched = false;
bool redTouched = false;
bool middleTouched = false; // middle square starts the random lines
bool touched = false;

void DrawSquares(void);
void UpdateSquares(void);

static void writeString(uint16_t x, uint16_t y, char* data)
{  
  for (int i = 0; i < strlen(data); i++)
    displayChar((x+i)*16, y, data[i]); // 16 spaces in between start of new char  
}

void setup()
{
  MyDelay(5000); 
  Serial.begin(115200);

  InitPin(GPIO_19, PIN_OUTPUT); // this is BL (A4 on schematic)
  InitPin(GPIO_7, PIN_OUTPUT);  // TFT_CS (D7 on schematic)
  InitPin(GPIO_3, PIN_OUTPUT);  // TFT_DC (D3 on schematic)
  InitPin(GPIO_5, PIN_INPUT);   // TFT_DC (D3 on schematic)
  SetPin(GPIO_6, true);         // TPR_CS - make sure touch driver is unselected 
  SetPin(GPIO_19, true);       

  SPI.begin();
  SPI.beginTransaction(SPISettings(6000000, MSBFIRST, SPI_MODE0));
  HAL_ScreenInit();
  ClearScreen(0,0,0);
  Touch_Init();

  // perform calibration, try as many times if calibration fails
  char* goodCal = "Calibrated"; // xy = 3,150
  char* badCal = "NOT"; // xy = 2, 130
  char* restartCal = "restarting"; // xy = 2, 130
  uint16_t i;
  bool res;
  do 
  {    
    ClearScreen(0,0,0);
    res = Calibrate_REStp();
    if (res == false)
    {    
      Log("not successful\n");
      ClearScreen(0,0,0);
      writeString(6, 120, badCal);
      writeString(3, 150, goodCal);
      MyDelay(1500); 
      ClearScreen(0,0,0);
      writeString(3, 150, restartCal);      
      MyDelay(1500);      
    }
    else 
    {
      Log("successful\n");
      ClearScreen(0,0,0);
      writeString(3, 150, goodCal);
    }
  } while (res == false);

  MyDelay(1000); 
  ClearScreen(0,0,0);
  DrawSquares();
  
  stride = 3;
  dx1 = stride;
  dx2 = stride;
  dy1 = stride;
  dy2 = stride;
  SS_x1 = 0; SS_x2 = 45; SS_y1 = 0; SS_y2 = 25;
  BlankingColor.Red = 0xFF;
  BlankingColor.Green = 0;
  BlankingColor.Blue = 0;
  LineColor.Red = 0;
  LineColor.Green = 0xFF;
  LineColor.Blue = 0xFF;

  Log("Startup Done\n");
}

void loop()
{  
  if ( MyMillis() >= Time2ReadTouch )
  {
    Time2ReadTouch = MyMillis() + 100;
    // check if there is something to read on the touch controller TSC2046
    if (digitalRead(GPIO_5) == 0) 
    {
      if (ReadTouch())
        UpdateSquares();
    }
  } 
  
  if (RandomLines == true)
  {          
    if ( MyMillis() >= Time2Draw )
    {
      Time2Draw = MyMillis() + 3;
  
      if (ChangeInterval++ == 800)
      {
        BlankingColor.Red += (45 + (8 * random(16)));
        BlankingColor.Green -= 55;
        BlankingColor.Blue += (25 + (8 * random(16)));
        ChangeInterval = 0;
      ClearScreen(0,0,0);
      }
      
      line(SS_x1, SS_y1, SS_x2, SS_y2, BlankingColor);

      if ((SS_x1 + dx1) < DISPLAY_PWIDTH)
        SS_x1 += dx1;
      else
        dx1 = -(2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_x1 + dx1) >= 0)
        SS_x1 += dx1;
      else
        dx1 = (2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_x2 + dx2) < DISPLAY_PWIDTH)
        SS_x2 += dx2;
      else
        dx2 = -(2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_x2 + dx2) >= 0)
        SS_x2 += dx2;
      else
        dx2 = (2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_y1 + dy1) < DISPLAY_PHEIGHT)
        SS_y1 += dy1;
      else
        dy1 = -(2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_y1 + dy1) >= 0)
        SS_y1 += dy1;
      else
        dy1 = (2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_y2 + dy2) < DISPLAY_PHEIGHT)
        SS_y2 += dy2;
      else
        dy2 = -(2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      if ((SS_y2 + dy2) >= 0)
        SS_y2 += dy2;
      else
        dy2 = (2 + ((stride * random(16)) >> 4)); // "random" number between 0 and 15 then divided by 16

      // Check check check
      if (SS_x1 < 0)
        SS_x1 = 0;
      if (SS_x1 >= DISPLAY_PWIDTH)
        SS_x1 = DISPLAY_PWIDTH - 1;

      if (SS_x2 < 0)
        SS_x2 = 0;
      if (SS_x2 >= DISPLAY_PWIDTH)
        SS_x2 = DISPLAY_PWIDTH - 1;

      if (SS_y1 < 0)
        SS_y1 = 0;
      if (SS_y1 >= DISPLAY_PHEIGHT)
        SS_y1 = DISPLAY_PHEIGHT - 1;

      if (SS_y2 < 0)
        SS_y2 = 0;
      if (SS_y2 >= DISPLAY_PHEIGHT)
        SS_y2 = DISPLAY_PHEIGHT - 1;

      line(SS_x1, SS_y1, SS_x2, SS_y2, LineColor);      
    }
  }
}

void UpdateSquares(void)
{
  static uint8_t lastUpdate = 2; // 0-green 1-red 2-white  
  color_type redBtn, grnBtn, clearBtn;  
  clearBtn.Red = 0x00;
  clearBtn.Green = 0x00;
  clearBtn.Blue = 0x00;
    
  grnBtn.Red = 0x00;
  grnBtn.Green = 0xFF;
  grnBtn.Blue = 0x00;
  
  redBtn.Red = 0xFF;
  redBtn.Green = 0x00;
  redBtn.Blue = 0x00;

  if (RandomLines)
  {
    if (touched)
    {
      RandomLines = false;  
      touched = false; 
      DrawSquares();      
      lastUpdate = 2; // back to white middle square            
    }
  }
  else 
  {
    if (greenTouched)    
    {
      if (lastUpdate != 0) // if not yet green
      {
        filledrect(89,  43, 146, 106, clearBtn);
        filledrect(89,  43, 146, 106, grnBtn);
        Log("Green drawn\n");
        lastUpdate = 0;
      }      
      greenTouched = false;
    }
    else if (redTouched)
    {
      if (lastUpdate != 1) // if not yet red
      {
        filledrect(89,  43, 146, 106, clearBtn);
        filledrect(89,  43, 146, 106, redBtn);
        Log("Red drawn\n");
        lastUpdate = 1;
      }              
      redTouched = false;      
    }
    else if (middleTouched)
    {      
      middleTouched = false;
      RandomLines = true; 
      ClearScreen(0,0,0);
    }
  }
}

void DrawSquares(void)
{  
  ClearScreen(0,0,0);
  color_type redBtn, grnBtn, waitBtn;
  waitBtn.Red = 0xFF;
  waitBtn.Green = 0xFF;
  waitBtn.Blue = 0xFF;
  rect(89,  43, 146, 106, waitBtn);
  
  grnBtn.Red = 0x00;
  grnBtn.Green = 0xFF;
  grnBtn.Blue = 0x00;
  rect(35,  186, 91, 250, grnBtn);

  redBtn.Red = 0xFF;
  redBtn.Green = 0x00;
  redBtn.Blue = 0x00;
  rect(141, 186, 198, 250, redBtn);  
}

void DebugPrint(char *str)
{
  Serial.print(str);
}

// A millisecond delay wrapper for the Arduino function
void MyDelay(uint32_t DLY)
{
  uint32_t wait;
  wait = millis() + DLY; while (millis() < wait);
}

// Externally accessible abstraction for millis()
uint32_t MyMillis(void)
{
  return millis();
}

// Interrupt Related Wrappers
void DisableInt(void)
{
  noInterrupts();
}

void EnableInt(void)
{
  interrupts();
}

// GPIO Related Wrappers
void InitPin(uint8_t PinNum, uint8_t PinMode)
{
  pinMode(PinNum, PinMode);
}

// An abstracted pin write that may be called from outside this file.
void SetPin(uint8_t pin, bool state)
{
  digitalWrite(pin, state);
}

// An abstracted pin read that may be called from outside this file.
uint8_t ReadPin(uint8_t pin)
{
  return (digitalRead(pin));
}

//====================================== SPI FUNCTION ABSTRACTIONS ============================================
// Send a byte through SPI as part of a larger transmission.  Does not enable/disable SPI CS
void SPI_Write(uint8_t data)
{
  //  Log("W-0x%02X\n", data);
  SPI.transfer(data);
}

uint8_t SPI_Read(void)
{
  return (SPI.transfer(0x00));
}

uint8_t SPI_RW(uint8_t data)
{
  return (SPI.transfer(data));
}

// Read a series of bytes from SPI and store them in a buffer
void SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length)
{
  //  uint8_t a = SPI.transfer(0x00); // dummy read
  while (Length--)
  {
    *(Buffer++) = SPI.transfer(0x00);
  }
}
