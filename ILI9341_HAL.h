/*
 * 
 *   Copyright (c) 2019 Matrix Orbital, Corp. https://www.matrixorbital.com/
 *   
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *   
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *   
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 *   
*/
#ifndef __ILI9341HAL_H
#define __ILI9341HAL_H

#ifdef __cplusplus
extern "C" {
#endif

// Basic Color definitions
#define COLOR_BLACK                         0x0000
#define COLOR_BLUE                          0x001F
#define COLOR_RED                           0xF800
#define COLOR_GREEN                         0x07E0
#define COLOR_CYAN                          0x07FF
#define COLOR_MAGENTA                       0xF81F
#define COLOR_YELLOW                        0xFFE0
#define COLOR_WHITE                         0xFFFF

#define DISPLAY_PWIDTH                         240
#define DISPLAY_PHEIGHT                        320

void HAL_ScreenInit(void);
void HAL_ScreenFill(uint8_t, uint8_t, uint8_t);
void HAL_ScreenWipe(uint8_t R, uint8_t G, uint8_t B);
void HAL_PutPixel(uint16_t, uint16_t, uint8_t, uint8_t, uint8_t);
void HAL_BoxWH(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t);
void HAL_DrawChar(uint16_t x, uint16_t y, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif

/*
Commands:

Set Column - 8.2.20 - Command 2Ah

Set Row - 8.2.21 - Command 2Bh

Both Set Column and Set Row are needed to define an are on the screen.  The first parameter in each is the
actual start column/row so sending the commands with the same columns and rows for both start and end will
result in a write area of one pixel.

Write - 8.2.22 - Command 2Ch
Write will set the display back to whatever location is currently set as start-column and start-page
or in other words, Start column and Start Row.  Writes continue to fill the defined write area and additional
data is ignored. In this way, the same area of the screen can be update again and again for animations.
Note that the MADCTL command can exchange columns for rows and rows for columns making the write command
act differently depending on the status of MADCTL

Read - 8.2.24 - Command 2Eh
Read will operate exactly the same as write including the effect of MADCTL except that the data sheet makes
it sound like it is mysteriously different.  I will refrain from further comment on the deep and abiding
hatred that I feel for all personnel involved with the creation of said documentation and will assume that
the reader appreciates that I wish them all severe cases of herpes and intestinal parasites.

Write Continue - 8.2.34 - Command 3Ch
It appears necessary that a write command be used before this command, but once started, writes continue in
exactly the fashion described in the above write command except that no further commands are required before
sending data.  Simply send this command and all the data to fill up the defined write area.  In the case
where animation is needed, the data can continue to be sent constantly (or with multiple write continue
commands) and the rows and columns will be reset back to start when the area is overrun, however the Frame
Memory Access and Interface setting (B3h) needs to be set to zero for this to happen otherwise additional
data will be ignored.

Read continue - 8.2.35 - Command 3Eh
This is the exact analog to the above command (3C) except for reads and operates in the same way except that
I would hope that coninuous reads of an area would be useless and extra setting should not be used.

Get Scanline - 8.2.37 - Command 45h
This command returns the current scan location on the display, but includes all the dead zones around the
active area.  I assume that this command would be useful to sync the writes to the display animation.

*/
