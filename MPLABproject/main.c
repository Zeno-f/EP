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

#define _XTAL_FREQ 8000000  // X-tal = 8 MHz
#define buttonPress1 PORTBbits.RB0
#define buttonPress2 PORTBbits.RB1

// verschillende variabelen voor het programma
int button1 = 0;
int button2 = 0;
int loop = 0;
int loopLicht = 0;
char ledArray[4] = {0x80,0x30,0x10,0x00};

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

	LATC = ledArray[loop];
	loop++;
	
	if (loop == 2)	{
		loop = 0;
	}
	
        __delay_ms(90);
		
	}
}
