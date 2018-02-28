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
int ledArray[3] = {0x80,0x30,0x10};

void main()
{
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
	
    while(1)	{
		
		if (buttonPress1 == 0)	{
			button1 = 1;
		}
		
		if	(buttonPress2 == 0)	{
			button2 = 1;
		}
		
		if	(button1 ^ button2)	{
			loopLicht = 1;
		}
		
		if (button1 & button2)	{
			loopLicht = 0;
			button1 = 0;
			button2 = 0;
		}
		
		if (loopLicht == 1)	{
			
			if	(loop > 2)	{
				loop = 0;
				LATC(ledArray[loop]);
				loop++;
			}
			
			else	{
				LATC(ledArray[loop]);
				loop++;
			}
		}
		
		delay(90);
		
	}
}
