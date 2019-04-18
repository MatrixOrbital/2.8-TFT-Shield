#include "touch.h"
#include "tsc2046.h"
#include "calibrate.h"
#include "graphic.h"


#ifndef ABS
#define ABS(x) (  ((int32_t)(x)) < 0 ? (-(x)) : (x))
#endif

#define ADS_START         (1 << 7)
#define ADS_A2A1A0_d_y    (1 << 4)  /* differential */
#define ADS_A2A1A0_d_z1   (3 << 4)  /* differential */
#define ADS_A2A1A0_d_z2   (4 << 4)  /* differential */
#define ADS_A2A1A0_d_x    (5 << 4)  /* differential */
#define ADS_A2A1A0_temp0  (0 << 4)  /* non-differential */
#define ADS_A2A1A0_vbatt  (2 << 4)  /* non-differential */
#define ADS_A2A1A0_vaux   (6 << 4)  /* non-differential */
#define ADS_A2A1A0_temp1  (7 << 4)  /* non-differential */
#define ADS_8_BIT         (1 << 3)
#define ADS_12_BIT        (0 << 3)
#define ADS_SER           (1 << 2)  /* non-differential */
#define ADS_DFR           (0 << 2)  /* differential */
#define ADS_PD10_PDOWN    (0 << 0)  /* lowpower mode + penirq */
#define ADS_PD10_ADC_ON   (1 << 0)  /* ADC on */
#define ADS_PD10_REF_ON   (2 << 0)  /* vREF on + penirq */
#define ADS_PD10_ALL_ON   (3 << 0)  /* ADC + vREF on */


#define READ_12BIT_DFR(d, adc, vref) (ADS_START | d \
  | ADS_12_BIT | ADS_DFR | \
  (adc ? ADS_PD10_ADC_ON : 0) | (vref ? ADS_PD10_REF_ON : 0))

#define READ_Y(vref)  (READ_12BIT_DFR(ADS_A2A1A0_d_y,  1, vref))
#define READ_Z1(vref) (READ_12BIT_DFR(ADS_A2A1A0_d_z1, 1, vref))
#define READ_Z2(vref) (READ_12BIT_DFR(ADS_A2A1A0_d_z2, 1, vref))
#define READ_X(vref)  (READ_12BIT_DFR(ADS_A2A1A0_d_x,  1, vref))
#define PWRDOWN       (READ_12BIT_DFR(ADS_A2A1A0_d_y,  0, 0))  /* LAST */

/* single-ended samples need to first power up reference voltage;
 * we leave both ADC and VREF powered
 */
#define READ_12BIT_SER(x) (ADS_START | x \
  | ADS_12_BIT | ADS_SER)

#define REF_ON  (READ_12BIT_DFR(ADS_A2A1A0_d_x, 1, 1))
#define REF_OFF (READ_12BIT_DFR(ADS_A2A1A0_d_y, 0, 0))


typedef struct
{
  unsigned int validatePattern1;
  MATRIX storedMatrix;
  unsigned int validatePattern2;  
} tStoredCalData;

static tStoredCalData storedCalData;
static tStoredCalData dat;
static unsigned int calibrated = 0;

static void TSC2046_ChipSelect(void)
{  
  SetPin(TSC2046_CS_PIN, 0);
}

static void TSC2046_ChipDeselect(void)
{
  SetPin(TSC2046_CS_PIN, 1);
}

static void TSC2046_PinInit(void)
{    
  // SPI initialization is done in ILI init             
  InitPin(TSC2046_CS_PIN, PIN_OUTPUT);
  TSC2046_ChipDeselect(); // deselect the TSC2046 for now
  return;
}

#define DEBOUNCE_MAX 10
#define DEBOUNCE_TOL  3

//#define pat1 0x32239081
//#define pat2 0xabdfadba

static uint16_t spiTransfer(uint8_t cmd)
{
  uint8_t data[3];
  uint8_t sdata[3];
  //SSP_DATA_SETUP_Type sspCfg;

  sdata[0] = cmd;
  sdata[1] = 0xff;
  sdata[2] = 0xff;

  TSC2046_ChipSelect();  
  for (int i = 0; i < 3; i++)
    data[i] = SPI_RW(sdata[i]);   
  TSC2046_ChipDeselect();

  int val = (data[1] << 8) | (data[2] );
  val = ((val >> 3) & 0xFFF) << 3;
  return val;  
}

static int32_t getFilteredValue(int p)
{
  int32_t a[7];
  int32_t tmp = 0;
  int i = 0, j = 0;

  /*
   * Median and averaging filter
   *
   * 1. Get 7 values
   * 2. Sort these values
   * 3. Take average of the 3 values in the middle
   */
    
  for (i = 0; i < 7; i++) {
    a[i] = spiTransfer(p);
  }

  // bubble sort
  for (i = 0; i < 7; i++) {
    for (j = 0; j < (7-(i+1)); j++) {
      if (a[j] > a[j+1]) {
        // swap
        tmp = a[j];
        a[j] = a[j+1];
        a[j+1] = tmp;
      }
    }
  }

  // average of 3 values in the middle
  return ((a[2]+a[3]+a[4])/3);
}

static void readAndFilter(int32_t *x, int32_t* y, int32_t* z)
{
  int32_t ix, iy, iz1, iz2 = 0;
  int32_t lastx, lasty, lastz1, lastz2 = 0;
  int i = 0;

  *x = 0;
  *y = 0;
  *z = 0;

  lasty = getFilteredValue(READ_Y(0));
  lasty >>= 3;
  if (lasty >= 4095) {
    lasty = 0;
  }

  //Log("lasty = %d\n",lasty);

  lastx = getFilteredValue(READ_X(0));
  lastx >>= 3;
  if (lastx >= 4095) {
    lastx = 0;
  }

  //Log("lastx = %d\n",lastx);

  lastz1 = getFilteredValue(READ_Z1(0));
  lastz1 >>= 3;

  lastz2 = getFilteredValue(READ_Z2(0));
  lastz2 >>= 3;


  if (lastx && lastz1) {
   *z = (lastx * ABS(lastz2 - lastz1)) / lastz1;
  }
  else {
   *z = 0;
  }

  if (*z > 10500) {
    *z = 0;
  }

  if (*z == 0) {
    //Log("Z = 0\n");
    return;
  }

  for (i = 0; i < DEBOUNCE_MAX; i++) {
    iy = getFilteredValue(READ_Y(0));
    iy >>= 3;

    if (ABS (lasty - iy) <= DEBOUNCE_TOL) {
      break;
    }

    lasty = iy;
  }

  for (i = 0; i < DEBOUNCE_MAX; i++) {
    ix = getFilteredValue(READ_X(0));
    ix >>= 3;
    if (ix > 4095) {
      ix = 0;
    }

    if (ABS (lastx - ix) <= DEBOUNCE_TOL) {
      break;
    }

    lastx = ix;
  }

  for (i = 0; i < DEBOUNCE_MAX; i++) {
    iz1 = getFilteredValue(READ_Z1(0));
    iz1 >>= 3;

    if (ABS (lastz1 - iz1) <= DEBOUNCE_TOL) {
      break;
    }

    lastz1 = iz1;
  }

  for (i = 0; i < DEBOUNCE_MAX; i++) {
    iz2 = getFilteredValue(READ_Z2(0));
    iz2 >>= 3;

    if (ABS (lastz2 - iz2) <= DEBOUNCE_TOL) {
      break;
    }

    lastz2 = iz2;
  }

  *x = ix;
  *y = iy;

  if (ix && iz1) {
   *z = (ix * ABS(iz2 - iz1)) / iz1;
  }
  else {
   *z = 0;
  }

  if (*z > 10500) {
    *z = 0;
  }

  //Log("                   %d,%d,%d\n",ix,iy,z);
}

void touch_xyz(int32_t* x, int32_t* y, int32_t* z)
{
  int32_t ix, iy, iz = 0;
  POINT displayPoint, screenSample;
  uint8_t pwrDown = PWRDOWN;
  
  readAndFilter(&ix, &iy, &iz);
  *z = iz;

  if (calibrated)
  {            
      //Log("applying matrix\n");
      screenSample.x = ix;
      screenSample.y = iy;
      getDisplayPoint( &displayPoint, &screenSample, &(storedCalData.storedMatrix) ) ;
      *x = displayPoint.x;
      *y = displayPoint.y;
  }
  else
  {          
    *x = ix;
    *y = iy;
  }   
  if (*z) 
  {
      Log("                   %d,%d,%d\n",*x,*y,*z);  
  }
}

void touch_calibrate(tTouchPoint ref1, tTouchPoint ref2, tTouchPoint ref3,
  tTouchPoint scr1, tTouchPoint scr2, tTouchPoint scr3)
{
  Log("We calibrate here\n");
  
  POINT disp[3];
  POINT scr[3];

  disp[0].x = ref1.x;
  disp[0].y = ref1.y;
  disp[1].x = ref2.x;
  disp[1].y = ref2.y;
  disp[2].x = ref3.x;
  disp[2].y = ref3.y;

  scr[0].x = scr1.x;
  scr[0].y = scr1.y;
  scr[1].x = scr2.x;
  scr[1].y = scr2.y;
  scr[2].x = scr3.x;
  scr[2].y = scr3.y;

  setCalibrationMatrix(disp, scr,
                       &storedCalData.storedMatrix);

  calibrated = true;

}


void touch_reinit(void)
{
  calibrated = false;
}


void TSC2046_init(uint32_t* initX, uint32_t* initY)
{     
  Log("touch pin init\n");  
  TSC2046_PinInit();    
    
  uint8_t data[3];  
  data[0] = REF_ON;
  data[1] = (READ_12BIT_SER(ADS_A2A1A0_vaux) | ADS_PD10_ALL_ON);
  data[2] = PWRDOWN;
   
  TSC2046_ChipSelect;  
  for (int i = 0; i <3; i++)
    SPI_Write(data[i]);
  TSC2046_ChipDeselect;

  // dummy read
  *initY = getFilteredValue(READ_Y(0));
  *initX = getFilteredValue(READ_X(0));
  Log("Y= %d\n",*initY);  
  Log("X= %d\n",*initX);  
  return;
}

extern bool RandomLines;
extern bool greenTouched;
extern bool redTouched;
extern bool middleTouched; // middle square starts the random lines
extern bool touched;
bool TSC2046_read(void)
{    
  int32_t x2, y2, z2;
  static int lastClr=2; // 0-green 1-red 2-white  
  
  touch_xyz(&x2, &y2, &z2);     
  if (z2)
  {
    if (RandomLines == false)
    {
      if (y2 >= 186 && y2 <= 250)  
      {
        if (x2 >= 35 && x2 <= 91)      
        {
          greenTouched = true;
        }
        else if (x2 >= 141 && x2 <= 198)      
        {
          redTouched = true;          
        }
      }
      else if (y2 >= 43 && y2 <= 106)
      {
        if (x2 >= 89 && x2 <= 146)              
          middleTouched = true;
      }
    }
    else 
    {
        touched = true;          
    }
    return 1;
  }
  return 0;    
}
