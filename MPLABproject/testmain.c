#define __18F25K80
#include "xc.h"
#include "fuses.h"
#include <stdio.h>

#define _XTAL_FREQ 8000000  // X-tal = 8 MHz

#define led1 LATC=0x20
#define led2 LATC=0x10
#define led3 LATC=0x80
#define leduit LATC=0x00
#define knop1 PORTBbits.RB0
#define knop2 PORTBbits.RB1

int button1 = 0;
int button2 = 0;

void main(void)	{
    // zet hier je statements neer

    TRISCbits.TRISC4 = 0; //aangeven van in-/ output '0' = output/ '1' = input
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC7 = 0;
    TRISBbits.TRISB0 = 1; //aangeven van in-/ output
    TRISBbits.TRISB1 = 1;
    ANCON1 = 0x00; //aangeven van digitale poorten (0 = digitaal)

	while(1)	{

		while ((knop1 == 0 || button1 == 1) && knop2 == 1)    {
			button1 = 1;
			led1; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);  //wachttijd (ms)
			led2; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);
			led3; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);

			if (knop2 == 0)	{				//maak de voorwaarde van de while niet waar  
				button1 = 0;
			}
		}

		leduit; //zet alle leds uit

		while ((knop2 == 0 || button2 == 1) && knop1 == 1)    {
			button2 = 1;
			led1; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);  //wachttijd (ms)
			led2; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);
			led3; //aansturen van uitgang dmv define (bovenin programma)
			__delay_ms(90);

			if (knop1 == 0)	{
				button2 = 0;
			}
		}

		leduit; //zet alle leds uit
	}
}

