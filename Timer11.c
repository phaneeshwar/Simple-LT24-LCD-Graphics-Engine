/*
 * Timer11.c

 *
 *  Created on: Mar 2, 2020
 *      Author: Eeshwar
 */
#include "Timer11.h"

volatile unsigned int *base_address_ptr = 0x00;

bool timer_intialized = false;
bool load_intialized = false;

#define Timer_Load      (0x00/sizeof(unsigned int))
#define Timer_counter   (0x04/sizeof(unsigned int))
#define Timer_control   (0x08/sizeof(unsigned int))
#define Timer_interrupt (0x0C/sizeof(unsigned int))

signed int Timer_intialise (unsigned int base_address)
{
	base_address_ptr = (unsigned int *) base_address;
	base_address_ptr[Timer_control] = 0x00;

	timer_intialized = true;

	return TIMER_SUCCESS;
}

bool Timer_isIntialised(void)
{
	return timer_intialized;
}

signed int Timer_load (unsigned int load)
{
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	load_intialized = true;
    base_address_ptr[Timer_Load] = load;

    return TIMER_SUCCESS;

}
bool Load_isIntialised(void)
{
	return load_intialized;
}


signed int Timer_Prescaler (unsigned int prescaler)
{
	unsigned int variable;
    unsigned int *timer_ptr;  // declare a seprate pointer
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;

	variable =  *base_address_ptr;
	timer_ptr = &variable;
	timer_ptr[Timer_control] &= 0x00FF;
	timer_ptr[Timer_control] |= (prescaler << 8 );
	base_address_ptr[Timer_control] |= timer_ptr[Timer_control];
	return TIMER_SUCCESS;
}

signed int Timer_Control (unsigned int control)
{
	unsigned int *timer_ptr1;
	unsigned int variable1;
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	if (!Load_isIntialised())  return TIMER_ERRORNOINT;

	variable1 = *base_address_ptr;
    timer_ptr1 = &variable1;
    timer_ptr1[Timer_control] &= ~0x7;
    timer_ptr1[Timer_control] = 0x7 & control;
    base_address_ptr[Timer_control] |= timer_ptr1[Timer_control];
    return TIMER_SUCCESS;
}

signed int Timer_counterread (void)
{

	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	if (!Load_isIntialised())  return TIMER_ERRORNOINT;
    return base_address_ptr[Timer_counter];
}

signed int Timer_interuppt(void)
{
	unsigned int value = 0;
	unsigned int *timer_ptr;
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	if (!Load_isIntialised())  return TIMER_ERRORNOINT;
	value = base_address_ptr[Timer_interrupt];

	if (value == 1)
	{
		base_address_ptr[Timer_interrupt] = 0x01;
	}

}


/*signed int Timer_read_interuppt(void )
{
	unsigned int value1 = 0x00;
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	if (!Load_isIntialised())  return TIMER_ERRORNOINT;
	return base_address_ptr[Timer_interrupt];

	}

signed int Timer_clear_interuppt(void)
{
	unsigned int variable;
	unsigned int *timer_ptr;
	if (!Timer_isIntialised()) return TIMER_ERRORNOINT;
	variable = *base_address_ptr;
	timer_ptr = &variable;
	timer_ptr[Timer_interrupt] |= 0x01;
	base_address_ptr[Timer_interrupt] |= timer_ptr[Timer_interrupt];
	//return TIMER_SUCCESS;

}
*/











