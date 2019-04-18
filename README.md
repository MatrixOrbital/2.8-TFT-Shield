# 2.8-TFT-Shield
An Arduino poject - control and use of a 2.8" (240320) TFT with resistive touch panel. Using Matrix Orbital's 2.8" TFT Shield for Arduino's MKR1000 (prototype as of date). All header files necessary are included.

This code contains functions to perform the following operations:
- initialize and configure 2.8" TFT screen (controller: ILI9341)
  - via SPI protocol (4 line, serial interface I)
  - BL control
- display simple graphic functions
  - lines (includes color definition)
  - rectangles (includes color definition)
  - filled rectangles (includes color definition)
  - text using basic 8x8 font (amplified width and height = 16x16)
- read screen touches (via resisitive touch driver: TSC2046)
- calibrate touch panel 
