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
#define button1 PORTBbits.RB0
#define button2 PORTBbits.RB1

// hiermee stel ik alleen deze twee bits in als input
TRISBbits.TRISRB0 = 1;
TRISBbits.TRISRB1 = 1;

// hiermee stel ik alleen deze 3 bits als output
TRISCbits.RC7 = 0;
TRISCbits.RC5 = 0;
TRISCbits.RC4 = 0;

TRISB = 0x03;

// verschillende variabelen voor het programma
int button1 = 0;
int button2 = 0;
int loop = 0;
int loopLicht = 0;
int ledArray[3] = {0x80,0x30,0x10};

ANCON1


void main()
{
    while(1)	{
		
		if (PORTRB0 == 0)	{
			button1 = 1;
		}
		
		if	(PORTRB1 == 0)	{
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
		
		delay(90)
		
	}
}
