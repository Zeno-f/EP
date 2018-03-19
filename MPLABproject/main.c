/*
 *	Embedded Programming 2018
 *
 *	Opdracht: Timers
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

#define button1 PORTbits.RB0
#define button2 PORTbits.RB1
#define yellow LATCbits.LATC7

void interrupt myIsr (void)	{
	
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF)	{
		INTCONbits.TMR0IF = 0;
		LATCbits.LATC4 = ~LATCbits.LATC4;
		TMR0H = 0x48;
		TMR0L = 0xE4;
	}
	
	if (INTCONbits.INT0E && INTCONbits.INT0F)	{
		yellow = 0;
		INTCONbits.TMR0IE = 0;
		INTCONbits.INT0F = 0;
	}
	
	if (INTCON3bits.INT1E && INTCON3bits.INT1F)	{
		yellow = 1;
		INTCONbits.TMR0IE = 1;
		INTCON3bits.INT1F = 0;
	}
}


void main() {
	
	// ini
	TRISC = 0x00;
	LATC = 0x00;
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	ANCON1bits.ANSEL10 = 0;
	ANCON1bits.ANSEL8 = 0;
	T0CON = 0b10000100;
	INTCON2bits.TMR0IP = 1;
	INTCONbits.TMR0IF = 0;
	INTCONbits.TMR0IE = 1;
	INTCON2bits.INTEDG0 = 0;
	INTCON3bits.INT1E = 1;
	INTCON2bits.INTEDG1 = 1;
	
	ei();
	
	while(1);
}
