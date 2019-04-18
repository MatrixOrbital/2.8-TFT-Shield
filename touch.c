#include "touch.h"
#include "tsc2046.h"

void Touch_Init(void)
{
  uint32_t X,Y;
  TSC2046_init(&X,&Y);
  return;   
}

bool ReadTouch(void)
{
  bool result = TSC2046_read();
  return result;          
}
