/*****************************************************************************
 *
 *   Copyright(C) 2011, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * Embedded Artists AB assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. Embedded Artists AB
 * reserves the right to make changes in the software without
 * notification. Embedded Artists AB also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 *****************************************************************************/
#ifndef __TSC2046_H_
#define __TSC2046_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>       
#include <stdbool.h>      

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
