/*
 *	Embedded Programming
 *
 *	Opdracht: Looplicht
 *
 *	Code  by Zeno Scheltens
 *
 */

#include <stdio.h>
#include <xc.h>
#include "fuses.h"

#define _XTAL_FREQ 8000000  // X-tal = 8 MHz
#define buttonPress1 PORTBbits.RB0
#define buttonPress2 PORTBbits.RB1

// verschillende variabelen voor het programma
int button1 = 0;
int button2 = 0;
int loop = 0;
char ledArray[4] = {0x80,0x20,0x10,0x00};

void loopLicht(void)	{
	
	LATC = ledArray[loop];
	loop++;
	if (loop == 3)	{
		loop = 0;
	}
}

void main() {
	// Ini fase
	
	// hiermee stel ik alleen deze twee bits in als input
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;

	// hiermee stel ik alleen deze 3 bits als output
	TRISCbits.TRISC7 = 0;
	TRISCbits.TRISC5 = 0;
	TRISCbits.TRISC4 = 0;
	
	// hiermee maak je digitale poorten van RB0 en RB1 voor de buttons
	ANCON1 = 0x00;
	
	// main fase
	
	while (1)	{
		
		loopLicht();
		__delay_ms(200);
	}
}