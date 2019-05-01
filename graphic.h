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
#ifndef GRAPHIC_H
#define GRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
} color_type;

extern color_type gCurColour;

void box(int16_t, int16_t, int16_t, int16_t, color_type);
void boxwh(int16_t, int16_t, uint16_t, uint16_t, color_type);
void hline(int16_t, int16_t, int16_t, color_type);
void rect(uint16_t, uint16_t, uint16_t, uint16_t, color_type);
void filledrect(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd, color_type Colour);
void line(int16_t, int16_t, int16_t, int16_t, color_type);
void displayChar(uint16_t x, uint16_t y, uint8_t data);

void ClearScreen(uint8_t R, uint8_t G, uint8_t B);

#ifdef __cplusplus
}
#endif

#endif
