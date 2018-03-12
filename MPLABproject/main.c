/*
 *	Embedded Programming 2018
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

// specific putch() function for this project, needed for printf()
void putch (char c)	{
	while (TXSTA1bits.TRMT == 0)	{
		TXREG1 = c;
	}
}

void main() {
	
	// Ini fase
	
	TRISCbits.TRISC6 = 0;	// Tx1 output
	PIE3bits.RC2IE = 0;		// disable Rx interrupt USART2
	PIE3bits.TX2IE = 0;		// disable Tx interrupt USART2
	PIE1bits.RC1IE = 0;		// disable Rx interrupt USART1
	PIE1bits.TX1IE = 0;		// disable Tx interrupt USART1
	TXSTA1 = 0xA0;			//
	RCSTA1 = 0x80;			//
	BAUDCON1 = 0xC0;		//
	SPBRG1 = 12;			//  
	
	// port settings
	
	TRISCbits.TRISC5 = 0;			// portC output
	LATCbits.LATC5 = 1;				// LED1 groen aan
	
	// variables 
	
	int i;
	
	// main fase
	
	while (1)	{
		for (i = 0;i < 100;i++)	{
			printf("test = %d\n\r", i);
		}
	}	
}
