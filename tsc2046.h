#ifndef __TSC2046_H_
#define __TSC2046_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <arduino.h>       
#include <stdint.h>       
#include <stdbool.h>      
#include <stdio.h>           
#include "ArduinoTFT28.h"    


#define TSC2046_CS_PIN  6

void TSC2046_init(uint32_t* initX, uint32_t* initY);
bool TSC2046_read(void);
void touch_xyz(int32_t* x, int32_t* y, int32_t* z);
void touch_calibrate(tTouchPoint ref1, tTouchPoint ref2, tTouchPoint ref3,
  tTouchPoint scr1, tTouchPoint scr2, tTouchPoint scr3);
void touch_reinit(void);

#ifdef __cplusplus
}
#endif

#endif
