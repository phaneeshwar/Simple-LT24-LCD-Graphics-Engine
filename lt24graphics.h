/*
 * lt24graphics.h
 *
 *  Created on: May 25, 2020
 *      Author: Eeshwar
 */

#ifndef LT24GRAPHICS_H_
#define LT24GRAPHICS_H_
#include <math.h>
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include <stdbool.h>

#define GRAPHICS_SUCCESS 0


signed int Graphics_initialise(unsigned int lcd_pio_base,unsigned int lcd_hw_base);
signed int  Graphics_drawBox(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour, bool noFill, unsigned short fillColour);
signed int  Graphics_drawCircle(unsigned int x, unsigned int y, unsigned int r, unsigned short colour, bool noFill, unsigned short fillColour);
signed int  Graphics_drawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour);
signed int  Graphics_drawTriangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int x3, unsigned int y3, unsigned short colour, bool noFill, unsigned short fillColour);
signed int Graphics_fill_Tri (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short fillColour);
signed int  Graphics_SetPixel (unsigned short colour,unsigned int x, unsigned int y);


#endif /* LT24GRAPHICS_H_ */
