/*
 *   File Name:  calibrate.c
 *
 *
 *   This file contains functions that implement calculations 
 *    necessary to obtain calibration factors for a touch screen
 *    that suffers from multiple distortion effects: namely, 
 *    translation, scaling and rotation.
 *
 *   The following set of equations represent a valid display 
 *    point given a corresponding set of touch screen points:
 *
 *
 *                                              /-     -\
 *              /-    -\     /-            -\   |       |
 *              |      |     |              |   |   Xs  |
 *              |  Xd  |     | A    B    C  |   |       |
 *              |      |  =  |              | * |   Ys  |
 *              |  Yd  |     | D    E    F  |   |       |
 *              |      |     |              |   |   1   |
 *              \-    -/     \-            -/   |       |
 *                                              \-     -/
 *
 * 
 *    where:
 *
 *           (Xd,Yd) represents the desired display point 
 *                    coordinates,
 *
 *           (Xs,Ys) represents the available touch screen
 *                    coordinates, and the matrix
 *
 *           /-   -\
 *           |A,B,C|
 *           |D,E,F| represents the factors used to translate
 *           \-   -/  the available touch screen point values
 *                    into the corresponding display 
 *                    coordinates.
 *
 *
 *    Note that for practical considerations, the utilitities 
 *     within this file do not use the matrix coefficients as
 *     defined above, but instead use the following 
 *     equivalents, since floating point math is not used:
 *
 *            A = An/Divider 
 *            B = Bn/Divider 
 *            C = Cn/Divider 
 *            D = Dn/Divider 
 *            E = En/Divider 
 *            F = Fn/Divider 
 *
 *
 *
 *    The functions provided within this file are:
 *
 *          setCalibrationMatrix() - calculates the set of factors
 *                                    in the above equation, given
 *                                    three sets of test points.
 *               getDisplayPoint() - returns the actual display
 *                                    coordinates, given a set of
 *                                    touch screen coordinates.
 * translateRawScreenCoordinates() - helper function to transform
 *                                    raw screen points into values
 *                                    scaled to the desired display
 *                                    resolution.
 *
 *
 */

#define _CALIBRATE_C_

/****************************************************/
/*                                                  */
/* Included files                                   */
/*                                                  */
/****************************************************/
#include <arduino.h>
#include <stdlib.h>
#include <string.h>
#include "touch.h"   
#include "tsc2046.h"
#include "calibrate.h"
#include "graphic.h"   
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/

/****************************************************/
/*                                                  */
/* Global variables                                 */
/*                                                  */
/****************************************************/

/****************************************************/
/*                                                  */
/* Forward Declaration of local functions           */
/*                                                  */
/****************************************************/



/**********************************************************************
 *
 *     Function: setCalibrationMatrix()
 *
 *  Description: Calling this function with valid input data
 *                in the display and screen input arguments 
 *                causes the calibration factors between the
 *                screen and display points to be calculated,
 *                and the output argument - matrixPtr - to be 
 *                populated.
 *
 *               This function needs to be called only when new
 *                calibration factors are desired.
 *               
 *  
 *  Argument(s): displayPtr (input) - Pointer to an array of three 
 *                                     sample, reference points.
 *               screenPtr (input) - Pointer to the array of touch 
 *                                    screen points corresponding 
 *                                    to the reference display points.
 *               matrixPtr (output) - Pointer to the calibration 
 *                                     matrix computed for the set 
 *                                     of points being provided.
 *
 *
 *  From the article text, recall that the matrix coefficients are
 *   resolved to be the following:
 *
 *
 *      Divider =  (Xs0 - Xs2)*(Ys1 - Ys2) - (Xs1 - Xs2)*(Ys0 - Ys2)
 *
 *
 *
 *                 (Xd0 - Xd2)*(Ys1 - Ys2) - (Xd1 - Xd2)*(Ys0 - Ys2)
 *            A = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Xs0 - Xs2)*(Xd1 - Xd2) - (Xd0 - Xd2)*(Xs1 - Xs2)
 *            B = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 Ys0*(Xs2*Xd1 - Xs1*Xd2) + 
 *                             Ys1*(Xs0*Xd2 - Xs2*Xd0) + 
 *                                           Ys2*(Xs1*Xd0 - Xs0*Xd1)
 *            C = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Yd0 - Yd2)*(Ys1 - Ys2) - (Yd1 - Yd2)*(Ys0 - Ys2)
 *            D = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Xs0 - Xs2)*(Yd1 - Yd2) - (Yd0 - Yd2)*(Xs1 - Xs2)
 *            E = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 Ys0*(Xs2*Yd1 - Xs1*Yd2) + 
 *                             Ys1*(Xs0*Yd2 - Xs2*Yd0) + 
 *                                           Ys2*(Xs1*Yd0 - Xs0*Yd1)
 *            F = ---------------------------------------------------
 *                                   Divider
 *
 *
 *       Return: OK - the calibration matrix was correctly 
 *                     calculated and its value is in the 
 *                     output argument.
 *               NOT_OK - an error was detected and the 
 *                         function failed to return a valid
 *                         set of matrix values.
 *                        The only time this sample code returns
 *                        NOT_OK is when Divider == 0
 *
 *
 *
 *                 NOTE!    NOTE!    NOTE!
 *
 *  setCalibrationMatrix() and getDisplayPoint() will do fine
 *  for you as they are, provided that your digitizer         
 *  resolution does not exceed 10 bits (1024 values).  Higher
 *  resolutions may cause the integer operations to overflow
 *  and return incorrect values.  If you wish to use these   
 *  functions with digitizer resolutions of 12 bits (4096    
 *  values) you will either have to a) use 64-bit signed     
 *  integer variables and math, or b) judiciously modify the 
 *  operations to scale results by a factor of 2 or even 4.  
 *
 *
 */
int setCalibrationMatrix( POINT * displayPtr,
                          POINT * screenPtr,
                          MATRIX * matrixPtr)
{
    int  retValue = OK ;

    
    matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                         ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
    if( matrixPtr->Divider == 0 )
    {
        Log("NOT OK\n");
        retValue = NOT_OK ;
    }
    else
    {
        matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                        ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
        matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                        ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
        matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
        matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                        ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    
        matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                        ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
        matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
        Log("OK\n");
    }
 
    return( retValue ) ;
} /* end of setCalibrationMatrix() */

/**********************************************************************
 *
 *     Function: getDisplayPoint()
 *
 *  Description: Given a valid set of calibration factors and a point
 *                value reported by the touch screen, this function
 *                calculates and returns the true (or closest to true)
 *                display point below the spot where the touch screen 
 *                was touched.
 * 
 *
 * 
 *  Argument(s): displayPtr (output) - Pointer to the calculated
 *                                      (true) display point.
 *               screenPtr (input) - Pointer to the reported touch
 *                                    screen point.
 *               matrixPtr (input) - Pointer to calibration factors
 *                                    matrix previously calculated
 *                                    from a call to 
 *                                    setCalibrationMatrix()
 * 
 *
 *  The function simply solves for Xd and Yd by implementing the 
 *   computations required by the translation matrix.  
 * 
 *                                              /-     -\
 *              /-    -\     /-            -\   |       |
 *              |      |     |              |   |   Xs  |
 *              |  Xd  |     | A    B    C  |   |       |
 *              |      |  =  |              | * |   Ys  |
 *              |  Yd  |     | D    E    F  |   |       |
 *              |      |     |              |   |   1   |
 *              \-    -/     \-            -/   |       |
 *                                              \-     -/
 * 
 *  It must be kept brief to avoid consuming CPU cycles.
 * 
 *
 *       Return: OK - the display point was correctly calculated 
 *                     and its value is in the output argument.
 *               NOT_OK - an error was detected and the function
 *                         failed to return a valid point.
 *
 *
 *
 *                 NOTE!    NOTE!    NOTE!
 *
 *  setCalibrationMatrix() and getDisplayPoint() will do fine
 *  for you as they are, provided that your digitizer         
 *  resolution does not exceed 10 bits (1024 values).  Higher
 *  resolutions may cause the integer operations to overflow
 *  and return incorrect values.  If you wish to use these   
 *  functions with digitizer resolutions of 12 bits (4096    
 *  values) you will either have to a) use 64-bit signed     
 *  integer variables and math, or b) judiciously modify the 
 *  operations to scale results by a factor of 2 or even 4.  
 *
 *
 */
int getDisplayPoint( POINT * displayPtr,
                     POINT * screenPtr,
                     MATRIX * matrixPtr )
{
    int  retValue = OK ;

    if( matrixPtr->Divider != 0 )
    {
            /* Operation order is important since we are doing integer */
            /*  math. Make sure you add all terms together before      */
            /*  dividing, so that the remainder is not rounded off     */
            /*  prematurely.                                           */
        displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                          (matrixPtr->Bn * screenPtr->y) + 
                           matrixPtr->Cn 
                        ) / matrixPtr->Divider ;
        displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                          (matrixPtr->En * screenPtr->y) + 
                           matrixPtr->Fn 
                        ) / matrixPtr->Divider ;
    }
    else
    {
        retValue = NOT_OK ;
    }
    return( retValue ) ;
} /* end of getDisplayPoint() */


/******************************************************************************
 * Local variables
 *****************************************************************************/

static int calibPoint = 0;

static tTouchPoint refPoint1 = { 15,  242};
static tTouchPoint refPoint2 = {240, 80};
static tTouchPoint refPoint3 = {460, 222};
static tTouchPoint refPoint4 = {460, 15};
static tTouchPoint scr1 = {0, 0};
static tTouchPoint scr2 = {0, 0};
static tTouchPoint scr3 = {0, 0};
static uint8_t releaseNeeded = false;
static uint8_t touchReleased = false;


/******************************************************************************
 * Local functions
 *****************************************************************************/

static void
drawCalibPoint(uint16_t x, uint16_t y)
{
  uint32_t Width, Height;
  uint32_t SQWidth, SQHeight;
  uint8_t Bpp;
  color_type color;

  color.Red = 255;
  color.Green = 255;
  color.Blue = 255;
  Width = 240;
  Height = 320;
  SQWidth = (int) (4 * 141 / 25.4); // make the squares 4mm x 4mm; pixel size is 0.18mm x 0.18mm
  SQHeight = (int) ( 4 * 141 / 25.4);
  Log("x1,y1,x2,y2 = %d %d %d %d\n", x-(SQWidth/2), y-(SQHeight/2), SQWidth+(x-(SQWidth/2)), SQHeight+(y-(SQHeight/2)));
  rect(x-(SQWidth/2), y-(SQHeight/2), SQWidth+(x-(SQWidth/2)), SQHeight+(y-(SQHeight/2)), color);  
}

static uint8_t 
calibrateStart(void)
{
  int32_t x, y, z = 0;

  uint8_t calibrated = false;
  releaseNeeded = false;
  calibPoint = 0;
  uint32_t Width, Height;
  uint8_t Bpp;
  Width = 240;
  Height = 320;
  drawCalibPoint(refPoint1.x, refPoint1.y);

  touch_xyz(&x, &y, &z);

  while (!calibrated) 
  {   

    touch_xyz(&x, &y, &z);

    if (z == 0)
    {
      touchReleased = true;
      continue;
    }

    if (releaseNeeded && !touchReleased)
      continue;

    touchReleased = false;


    switch (calibPoint++)
    {
    case 0:
      scr1.x = x;
      scr1.y = y;
      drawCalibPoint(refPoint2.x, refPoint2.y);      
      releaseNeeded = true;
      break;
    case 1:
      scr2.x = x;
      scr2.y = y;
      drawCalibPoint(refPoint3.x, refPoint3.y);
      releaseNeeded = true;
      break;
    case 2:
      scr3.x = x;
      scr3.y = y;
      drawCalibPoint(refPoint4.x, refPoint4.y);
      touch_calibrate(refPoint1, refPoint2, refPoint3, scr1, scr2, scr3);
      releaseNeeded = true;
      break;
    case 3:            
      // a precision of 30 pixels x and y      
      if ((x <= (refPoint4.x +15) && x >= (refPoint4.x -15)) && (y <= (refPoint4.y +15) && y >= (refPoint4.y -15))) 
      {        
        calibrated = true;
      }
      else 
      {
        Log("BADDDDDDDDDDDDDDDDDDDDDDD :( \n");
      }
      return calibrated;      
      break;
    }
  }
  
  return false;
}


uint8_t Calibrate_REStp(void)
{
  uint32_t Width, Height;
  uint8_t Bpp;
  Width = 240;
  Height = 320;  
    
  // Make sure that the touch screen is not already calibrated
  touch_reinit();
  
  // Adjust calibration points to screen

  // Bottom left corner
  refPoint1.x = 15;
  refPoint1.y = Height - 15;
    
  // Sort of top horizontal center
  refPoint2.x = Width / 2;
  refPoint2.y = (Height / 2) - 15;
    
  // Bottom right corner
  refPoint3.x = Width - 15;
  refPoint3.y = Height - 15;
    
  // Test Point - top right corner
  refPoint4.x = Width - 15;
  refPoint4.y = 15;  

  Log ("Start Calibrating here \n");
  if (calibrateStart() == 1)
    return 1;
  else 
    return 0;  
}
