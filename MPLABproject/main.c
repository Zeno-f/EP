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
	
	// software interrupt
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF)	{		// enables TMR0 overflow interrupt - TMR0 reached overflow?
		INTCONbits.TMR0IF = 0;							// reset TMR0, clears the overflow
		LATCbits.LATC4 = ~LATCbits.LATC4;
		// offset, 18661
		TMR0H = 0x48;									// 72
		TMR0L = 0xE5;									// 229
	}
	
	if (INTCONbits.INT0E && INTCONbits.INT0F)	{		// enables external interrupt - did the interrupt happen
		yellow = 0;
		INTCONbits.TMR0IE = 0;							// disables TMR0 interrupt
		INTCONbits.INT0F = 0;							// clears this interrupt
	}
	
	if (INTCON3bits.INT1E && INTCON3bits.INT1F)	{	// enables external interrupt - did the interrupt happen
		yellow = 1;
		INTCONbits.TMR0IE = 1;							// enables TMR0 interrupt
		INTCON3bits.INT1F = 0;							// clears this interrupt
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
	T0CON = 0b10000110;				// enables timer 1 as 16 bit with a /128 prescale
	INTCON2bits.TMR0IP = 1;			// overflow interrupt priority
	INTCONbits.TMR0IF = 0;			// clears the timer overflow
	INTCONbits.TMR0IE = 1;			// enables the timer interrupt	
	INTCON2bits.INTEDG0 = 0;		// interrupt on rising/falling
	INTCONbits.INT0E = 1;			// enables external interrupt on button 1
	INTCON3bits.INT1E = 1;			// enables external interrupt on button 2
	INTCON2bits.INTEDG1 = 1;		// interrupt on rising/falling
	
    // enables all interrupts
	ei();
	
	while(1);
}