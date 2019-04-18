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
