// ties in both resistive and capacitive touch - mXT224e.h and tsc2046_touch.h
#ifndef __TOUCH_H
#define __TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <arduino.h>       
#include <stdint.h>       
#include <stdbool.h>      
#include <stdio.h>              
#include "ArduinoTFT28.h"

typedef struct
{
  int x;
  int y;
} tTouchPoint;

void Touch_Init(void);
bool ReadTouch(void);

#ifdef __cplusplus
}
#endif

#endif /* end __TOUCH_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
