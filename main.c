/*
 * main.c
 *
 *  Created on: May 25, 2020
 *      Author: Eeshwar
 */

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "Timer11/Timer11.h"
#include "lt24graphics.h"
#include <math.h>
#include <stdlib.h>


void exitOnFail(signed int status, signed int successStatus)
{
    if (status != successStatus)
    {
        exit((int)status);
    }
}

int main(void) {

	     volatile unsigned int base_add = 0xFFFEC600;
	     volatile unsigned int load = 0x00;
	     volatile unsigned int control = 0x0003;
	     volatile unsigned int prescaler = 0x00;
	     unsigned int timer_interrupt = 0;
	     unsigned int Starttimer = 0;
	     unsigned int Endtimer = 0;
	     unsigned int duration = 0;
	     float FPS = 0;


	    load = 0xFFFFFFFF;
		exitOnFail (Timer_intialise(base_add),TIMER_SUCCESS);
		        exitOnFail (Timer_load(load),TIMER_SUCCESS);
		        exitOnFail (Timer_Prescaler(prescaler),TIMER_SUCCESS);
		        exitOnFail (Timer_Control(control),TIMER_SUCCESS);
		        ResetWDT();
      while(1)
      {

    	Starttimer = Timer_counterread();

		exitOnFail (Graphics_initialise(0xFF200060,0xFF200080),GRAPHICS_SUCCESS); ResetWDT();
		//Rectangle. Red Border. Grey Fill.

		exitOnFail (Graphics_drawBox(10,10,230,310,LT24_RED,false,0x39E7),GRAPHICS_SUCCESS); ResetWDT();
		//Circle. Blue Border, White Fill. Centre of screen. 100px radius
		exitOnFail (Graphics_drawCircle(120,160,100,LT24_RED,false,LT24_GREEN),GRAPHICS_SUCCESS); ResetWDT();
		//Circle. Yellow Border, No Fill. Centre of screen. 102px radius
		exitOnFail (Graphics_drawCircle(120,160,102,LT24_BLUE,false,0),GRAPHICS_SUCCESS); ResetWDT();
		//Rectangle. Cyan Border, No Fill.
		exitOnFail (Graphics_drawBox(49,89,191,231,LT24_CYAN,false,LT24_GREEN),GRAPHICS_SUCCESS); ResetWDT();
		//Line. Green. 45 degree Radius of circle.
		exitOnFail (Graphics_drawLine(191,89,120,160,LT24_GREEN),GRAPHICS_SUCCESS); ResetWDT();
		//Line. Magenta. 270 degree Radius of circle.
		exitOnFail (Graphics_drawLine(120,160,20,160,LT24_MAGENTA),GRAPHICS_SUCCESS); ResetWDT();
		//Triangle. Blue Border, No Fill. Bottom left corner. Right-angle triangle.
		exitOnFail (Graphics_drawTriangle(18,283,18,302,37,302,LT24_BLUE,false,0),GRAPHICS_SUCCESS); ResetWDT();
		//Triangle. Yellow Border, Green Fill. Bottom left corner Equilateral triangle.
		exitOnFail (Graphics_drawTriangle(213,283,204,302,222,302,LT24_YELLOW,false,LT24_GREEN),GRAPHICS_SUCCESS);ResetWDT();
		//Done.

         Endtimer = Timer_counterread();
         duration = Starttimer - Endtimer;
         FPS = 1/(4.44e-9 * duration);

	while (1) { HPS_ResetWatchdog(); } //Watchdog reset.
	}
}

