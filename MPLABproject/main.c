/*
 * File:   main.c
 * Author: Zeno
 *
 * Created on 15 februari 2018, 9:38
 */

#include <xc.h>

#define _XTAL_FREQ 8000000  // X-tal = 8 MHz

void main(void)
{
    TRISC = 0x00;
	
	LATC = 0xB0;

	while(1);
}
