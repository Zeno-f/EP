/*
 *	Embedded Programming
 *
 *	Opdracht: Serieuze Communicatie
 *
 *	Code by 
 *		- Zeno Scheltens
 *		- Kit Yi Feng
 *
 */

#include <stdio.h>
#include <xc.h>
#include "fuses.h"

#define _XTAL_FREQ 8000000  // X-tal = 8 MHz

// shady code to be able to use printf with the microchip
void putch (char c)	{
	while (TXSTA1bits.TRMT == 0)	{
		'transmit register' = c;
	}
}

void main() {
	
	// Ini fase
	
	TRISCbits.TRISC6 = 0;	// Tx1 output
	PIE3bits.RC2IE = 0;		// disable Rx interrupt USART2
	PIE3bits.TX2IE = 0;		// disable Tx interrupt USART2
	PIE1bits.RC1IE = 0;		// disable Rx interrupt USART1
	PIE1bits.TX1IE = 0;		// disable Tx interrupt USART1
	TXSTA1 = ????;			//
	RCSTA1 = ????;			//
	BAUDCON1 = ????;		//
	SPBRG1 = ????;			//
	
	// port settings
	
	TRISC = ????;			// portC output
	LATC = ????;			// LED1 groen aan
	
	// variables 
	
	int ????;
	
	// main fase
	
	while (1)	{
		for ('range aangeven')	{
			printf("test = %d\n\r", ????);
		}
	}	
}
