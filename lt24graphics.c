/*
 * lt24graphics.c

 *
 *  Created on: May 25, 2020
 *      Author: Eeshwar
 */
#include "lt24graphics.h"
#include <math.h>

signed int  Graphics_drawTriangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short colour, bool noFill, unsigned short fillColour)
{

	if (!noFill)   // to check if the triangle needed to be filled or not
	{
		Graphics_fill_Tri (x1,y1,x2,y2,x3,y3,fillColour); ResetWDT(); // this fnction is used for filling up all the pixels in the region of interest
		Graphics_fill_Tri (x3,y3,x1,y1,x2,y2,fillColour); ResetWDT();
		Graphics_fill_Tri (x2,y2,x3,y3,x1,y1,fillColour); ResetWDT();
	}

	Graphics_drawLine (x1,y1,x2,y2,colour);  // drawline function is used for joining two coordinate points, Hence if all the three coordinates
	Graphics_drawLine (x2,y2,x3,y3,colour); //.... are joined then we obtain a triangle
	Graphics_drawLine (x3,y3,x1,y1,colour);

	return GRAPHICS_SUCCESS;        // to return true if the function is executed without any errors

}

signed int  Graphics_fill_Tri (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned short fillColour)
{
	int diffx = abs(1.0*(x2 - x1));           // obtain the difference between the two x-coordinate values. here absolute function is used. and respective deltas are calculated
	int diffy = -abs(1.0*(y2-y1));

	int err1 = diffx + diffy;  // to calculate the error function
	int err2;
    int kx = x1<x2 ? 1 : -1; // assign the kx and ky to either -1 or +1 depending on the position of the coordinates x1,x2 and y1,y2 respectively.
	int ky = y1<y2 ? 1 : -1;

	while (1)
	{
		Graphics_drawLine (x3,y3,x1,y1,fillColour); // to draw the line with the fill colour given byt the user

		if (x1 == x2 && y1 == y2)
		{
			break;
		}
		err2 = 2 * err1;            // to avoid floating point values hence error is determined.
		if (err2 >= diffy)         //.. it acts like a decision parameter, and to keep track of the pixel value.
		{
			err1 = err1 + diffy;
			x1 = x1 + kx;
		}
		if (err2 <= diffx)
		{
			err1 = err1 + diffx;
			y1 = y1 + ky;
		}
	}

	return GRAPHICS_SUCCESS;   // to return true if the function is executed without any errors

}

signed int  Graphics_drawLine (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour) {

	int diffx = abs(1.0 * (x2 - x1));  // obtain the difference between the two x-coordinate values. here absolute function is used. and respective deltas are calculated
	int diffy = -abs(1.0* (y2 - y1));

	int err1 = diffx + diffy;
	int err2;

	int kx = x1<x2 ? 1:-1;
	int ky = y1<y2 ? 1:-1;

	while(1)
	{
		Graphics_SetPixel(colour,x1,y1);

		if (x1 == x2 && y1 == y2)
		{
			break;
		}
		err2 = 2 * err1;   // this equation is used to avoid floating point values
		//... Also to determine which pixel to set high based on the degree of closeness from the original line to the midpoint of the pixel
		// ... Bresenhams line algorithm has been utilized. Slope error is used to determine the required pixel.

		if (err2 >= diffy)
		{
			err1 = err1 + diffy;
			x1 = x1 + kx;
		}

		if (err2 <= diffx)
		{
			err1 = err1 + diffx;
			y1 = y1 + ky;
		}
	}
	return GRAPHICS_SUCCESS; // to return true if the function is executed without any errors
}

signed int  Graphics_drawCircle (unsigned int x, unsigned int y, unsigned int r, unsigned short colour, bool noFill, unsigned short fillColour)
{
	// Circle determined using concept of pythagorous theorem
	int rad1 = (int) r;
	int rad2 = rad1*rad1;
	int threshold = 230;  // to outline the threhold value, used to set pixels within the scope tof the defined region
	int pythagorous = 0;  // using pythagorous theorem , this variable is used for determining the hypotaneous
	int xc = 0;
	int yc = 0;


	for (xc = -rad1-3; xc <= rad1 + 3; xc++)
	{
		for(yc = -rad1-3; yc <= rad1 + 3; yc++)
		{
			pythagorous = (xc*xc) + (yc*yc);
			// if nofill is true then fill outline of circle with colour parameter
			if (noFill && (pythagorous > rad2-threshold) && (pythagorous <= rad2))
			{
				Graphics_SetPixel(colour, xc+x,yc+y);
			}
			// if nofill is false then fill outline of circle with fillcolour parameter
			else if(!noFill && pythagorous <= rad2)
			{
				Graphics_SetPixel (fillColour, xc+x,yc+y);
			}
		}
	}

	// This function is used to set user defined colour within the defined circle region
	//...... all the pixels within the region of interest are assigned high.
	if(~noFill)
	{
		xc = 0;
		yc = 0;

		for (xc = -rad1-3;xc <= rad1+3; xc++)
		{
			for (yc = -rad1-3;yc <= rad1+3; yc++)
			{
				pythagorous = (xc*xc) + (yc*yc);
				if ((pythagorous > rad2-threshold)&&(pythagorous <= rad2))
				{
					Graphics_SetPixel(colour,xc+x,yc+y);
				}
			}
		}
	}
	return GRAPHICS_SUCCESS; // to return true if the function is executed without any errors
}

signed int  Graphics_drawBox (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short colour, bool noFill, unsigned short fillColour)
{
	int X1 = (int) x1;
	int X2 = (int) x2;
	int Y1 = (int) y1;
	int Y2 = (int) y2;

	int H = abs(1.0*(Y2 - Y1));  // Height and Width of the box is determined
	int W = abs(1.0*(X1 - X2)); //... Used for determing the coordinates for remaining points

	int i=0;
	int j=0;
	int z1=0;
	int z2=0;

	int kx = X1<X2 ? X1:X2;
	int ky = Y1<Y2 ? Y1:Y2;

	// This conditional statement below is used for setting up all the pixels in the given dimensions of the box
	if(!noFill)
	{
		for (i = 0; i<= H; i++)
		{
			for (j=0; j<= W; j++)
			{
				Graphics_SetPixel(fillColour, j+kx, i+ky);
			}
		}
	}

	// if nofill is true then only outline of the box is drawn
	//... two vertical lines are drawn using two for loops
	for (z1 = 0; z1 <= H; z1++)
	{
		Graphics_SetPixel(colour, X1, ky+z1);
	}

	for (z1 = 0; z1 <= H; z1++)
		{
			Graphics_SetPixel(colour, X2, ky+z1);
		}
	//..//... two horizontal lines are drawn using two for loops

	for (z2 = 0; z2 <= W; z2++)
			{
				Graphics_SetPixel(colour, kx+z2, Y1);
			}

	for (z2 = 0; z2 <= W; z2++)
			{
				Graphics_SetPixel(colour, kx+z2, Y2);
			}

	return GRAPHICS_SUCCESS; // to return true if the function is executed without any errors
}

signed int  Graphics_initialise(unsigned volatile int lcd_pio_base, unsigned volatile int lcd_hw_base)
{
	LT24_initialise(lcd_pio_base,lcd_hw_base); // used for initialising LT24 display
	return GRAPHICS_SUCCESS;
}

signed int  Graphics_SetPixel(unsigned short colour,unsigned int x, unsigned int y)
{
	LT24_drawPixel(colour,x,y);  // to set pixel colour for the selected pixel on the display.
	ResetWDT();
	return GRAPHICS_SUCCESS;
}
