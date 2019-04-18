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

  //  MO_ILI_Send(COMMAND,0xB5); //VERTICAL PORCH
  //  MO_ILI_Send(DATA,0x02);     //
  //  MO_ILI_Send(DATA,0x02);     //
  //  MO_ILI_Send(DATA,0x38);     //HORIZONTAL PORCH
  //  MO_ILI_Send(DATA,0x38);     //

  
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


//  // display write test RAQUEL ==============
//  ILI9341_Select();   
//  ILI9341_WriteCommand(0x2A); 
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x0A);
//  ILI9341_Deselect();         
//
//  ILI9341_Select();   
//  ILI9341_WriteCommand(0x2B);
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x00);
//  ILI9341_WriteData(0x0A);
//  ILI9341_Deselect();         
//
//  ILI9341_Select();   
//  ILI9341_WriteCommand(0x2C);
//  for (int i = 0; i < 255; i++)
//  {
//
//    ILI9341_WriteData(0xFF);
//    ILI9341_WriteData(0x00);
//    ILI9341_WriteData(0xFF);    
//  }
//  ILI9341_Deselect();   
//
//  ILI9341_Select();   
//  ILI9341_WriteCommand(0x00); // NOP
//  ILI9341_Deselect();      
//  // display write test ==============  
    
  
  /*
  ILI9341_Reset();

  //software reset
  ILI9341_WriteCommand(0x01);                                                            // Software reset
  MyDelay(100);                                                                          // for 100 ms

//  ILI9341_WriteCommand(0x11);
//  ILI9341_WriteData(0x00);

  ILI9341_Write1Data(0x11, 0x00);                                                        // exit sleep mode
  MyDelay(100);                                                                          // for 100 ms
  ILI9341_WriteCommand(0x29);                                                            // display on command
  ILI9341_WriteCommand(0xCD);                                                                // Power Control A (as per Atmel)
  ILI9341_WriteData(0x39);
  ILI9341_WriteData(0x2C);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x34);
  ILI9341_WriteData(0x02);

  ILI9341_WriteCommand(0xCF);                                                                // Power Control B (as per Atmel)
  ILI9341_WriteData(0x00);                                                                   // 0x00 per Atmel, 0x00 per fabienroyer
  ILI9341_WriteData(0xAA);                                                                   // 0xAA per Atmel, 0x83 per fabienroyer
  ILI9341_WriteData(0xB0);                                                                   // 0xB0 per Atmel, 0x30 per fabienroyer

  ILI9341_Write1Data(0xF7, 0x30);                                                        // Charge Pump Ratio Control (0x30 per Atmel, 0x20  per fabienroyer)
  ILI9341_Write1Data(0xC0, 0x25);                                                        // Power Control 1 (0x26 per Atmel 0x26 per fabienroyer)
  ILI9341_Write1Data(0xC1, 0x01);                                                        // Power Control 2 (0x11 as per Atmel (stupid))
  ILI9341_Write2Data(0xC5, 0x5C, 0x4C);                                                  // VCOM control 1 (as per Atmel)
//  ILI9341_WriteData(0xC7); ILI9341_WriteData(0x94);                                        // VCOM control 2 (as per Atmel)
  ILI9341_Write1Data(0xC7, 0xBD);                                                        // VCOM control 2
  ILI9341_Write3Data(0xE8, 0x85, 0x01, 0x78);                                            // Driver Timing Control A (as per Atmel)
  ILI9341_Write2Data(0xEA, 0x00, 0x00);                                                  // Driver Timing Control B (as per Atmel)
  ILI9341_Write1Data(0x3A, 0x05);                                                        // pixel format - 05 = 16 bit per pixel, 06 = 18
  ILI9341_Write1Data(0x36, 0x00);                                                        // memory access control = 40. BGR is 48
  ILI9341_Write1Data(0x51, 0xFF);                                                        // Set display brightness maximum
  ILI9341_Write3Data(0xF6, 0x00, 0x30, 0x40);                                            // Interface Control - Zero LSb for Red and Blue in 16 bit mode - Little Endian

  ILI9341_ColorSet(); // Send 128 bytes of data for 16 to 18 bit conversion


  /*
  ILI9341_WriteCommand(0x28);                                                                // display off command
  ILI9341_WriteCommand(0xC0); ILI9341_WriteData(0x23); //ILI9341_WriteData(0x04);  // power control 1
  ILI9341_WriteCommand(0xC1); ILI9341_WriteData(0x04);                                  // power control 2
  ILI9341_WriteCommand(0xC5); ILI9341_WriteData(0x2B); ILI9341_WriteData(0x25);    // VCOM control 1
  ILI9341_WriteCommand(0xC7); ILI9341_WriteData(0xbd);                                  // VCOM control 2
  ILI9341_WriteCommand(0x36); ILI9341_WriteData(0x40);                                  // memory access control = 40. BGR is 48
  ILI9341_WriteCommand(0x3A); ILI9341_WriteData(0x06);                                  // pixel format - 05 = 16 bit per pixel, 06 = 18
  ILI9341_WriteCommand(0xB1); ILI9341_WriteData(0x00); ILI9341_WriteData(0x1B);    // frame rate control = 1B, was 18

  ILI9341_WriteCommand(0xf2); ILI9341_WriteData(0x00);                                  // 3 Gamma disable **** COMMAND NOT LISTED
  ILI9341_WriteCommand(0x26); ILI9341_WriteData(0x01);                                  // Gamma set curve 1
*/
  /*
  ILI9341_WriteCommand(0xE0);
  ILI9341_WriteData(0x0F);                 //positive gamma correction
  ILI9341_WriteData(0x26);
  ILI9341_WriteData(0x21);
  ILI9341_WriteData(0x0B);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x51);
  ILI9341_WriteData(0x6F);
  ILI9341_WriteData(0x43);
  ILI9341_WriteData(0x0D);
  ILI9341_WriteData(0x1A);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x0C);
  ILI9341_WriteData(0x0A);
  ILI9341_WriteData(0x00);
*/
  /*
  ILI9341_WriteCommand(0xE1);
  ILI9341_WriteData(0x00);                 //negative gamma correction
  ILI9341_WriteData(0x19);
  ILI9341_WriteData(0x1E);
  ILI9341_WriteData(0x04);
  ILI9341_WriteData(0x11);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x2E);
  ILI9341_WriteData(0x09);
  ILI9341_WriteData(0x3C);
  ILI9341_WriteData(0x02);
  ILI9341_WriteData(0x05);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x33);
  ILI9341_WriteData(0x35);
  ILI9341_WriteData(0x0F);
*/
  /*
  ILI9341_WriteCommand(0x2A);              //start 0x0000
  ILI9341_WriteData(0x00);                 //column address set
  ILI9341_WriteData(0x00);                 // ********************************************************************
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0xEF);                 //end 0x00EF

  ILI9341_WriteCommand(0x2B);
  ILI9341_WriteData(0x00);                 //page address set
  ILI9341_WriteData(0x00);                 //start 0x0000 ******************************************************************************
  ILI9341_WriteData(0x01);
  ILI9341_WriteData(0x3F);                 //end 0x013F
*/
//  ILI9341_WriteCommand(0xB7); ILI9341_WriteData(0x07);                                //entry mode set
//  ILI9341_WriteCommand(0xB6);                                                              //display function control
//  ILI9341_WriteData(0x0A);
//  ILI9341_WriteData(0x82);
//  ILI9341_WriteData(0x27);
//  ILI9341_WriteData(0x00);
/*
  ILI9341_WriteCommand(0x11); ILI9341_WriteData(0x00);  // exit sleep mode
  ILI9341_WriteCommand(0x29);                                // display on command
*/
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

void ILI9341_ReadDisplaySignalMode(uint8_t *Parm)
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
