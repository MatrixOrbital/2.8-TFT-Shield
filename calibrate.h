/*
 *
 *   Copyright (c) 2001, Carlos E. Vidales. All rights reserved.
 *
 *   This sample program was written and put in the public domain 
 *    by Carlos E. Vidales.  The program is provided "as is" 
 *    without warranty of any kind, either expressed or implied.
 *   If you choose to use the program within your own products
 *    you do so at your own risk, and assume the responsibility
 *    for servicing, repairing or correcting the program should
 *    it prove defective in any manner.
 *   You may copy and distribute the program's source code in any 
 *    medium, provided that you also include in each copy an
 *    appropriate copyright notice and disclaimer of warranty.
 *   You may also modify this program and distribute copies of
 *    it provided that you include prominent notices stating 
 *    that you changed the file(s) and the date of any change,
 *    and that you do not charge any royalties or licenses for 
 *    its use.
 * 
 *
 * 
 *   File Name:  calibrate.h
 *
 *
 *   Definition of constants and structures, and declaration of functions 
 *    in Calibrate.c
 *
 */
#ifndef _CALIBRATE_H_
#define _CALIBRATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************/
/*                                                  */
/* Included files                                   */
/*                                                  */
/****************************************************/
#include <arduino.h>

/****************************************************/
/*                                                  */
/* Definitions                                      */
/*                                                  */
/****************************************************/
#ifndef		EXTERN
	#define		EXTERN         extern
#endif

#ifndef		OK
	#define		OK		        0
	#define		NOT_OK		   -1
#endif

#define			INT64				int64_t


/****************************************************/
/*                                                  */
/* Structures                                       */
/*                                                  */
/****************************************************/

typedef struct Point {
                        INT64    x,
                                 y ;
                     } POINT ;

typedef struct Matrix {
							/* This arrangement of values facilitates 
							 *  calculations within getDisplayPoint() 
							 */
                        INT64    An,     /* A = An/Divider */
                                 Bn,     /* B = Bn/Divider */
                                 Cn,     /* C = Cn/Divider */
                                 Dn,     /* D = Dn/Divider */
                                 En,     /* E = En/Divider */
                                 Fn,     /* F = Fn/Divider */
                                 Divider ;
                     } MATRIX ;


/****************************************************/
/*                                                  */
/* Function declarations                            */
/*                                                  */
/****************************************************/

EXTERN int setCalibrationMatrix( POINT * display,
                                 POINT * screen,
                                 MATRIX * matrix) ;

EXTERN int getDisplayPoint( POINT * display,
                            POINT * screen,
                            MATRIX * matrix ) ;

EXTERN uint8_t Calibrate_REStp(void);

EXTERN uint8_t loadCalibrationFromFile (void); 

#ifdef __cplusplus
}
#endif

#endif  /* _CALIBRATE_H_ */
