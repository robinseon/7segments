/*
 * 7segment.c
 *
 * Created: 01/04/2022 09:22:49
 * Author : robin
 */ 

#include <avr/io.h>
#include "Display/segment.h"
#include "Display/adc.h"
#include <avr/interrupt.h>

int main(void)
{
	init_display();
	adc_init();
	time_init();
			
    /* Replace with your application code */
    while (1) 
    {

    }
}

