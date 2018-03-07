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
int loop = 0;
unsigned char ledArray[4] = {0x80,0x20,0x10,0x00};

// functie voor het looplicht
void loopLicht(void)	{
	
	// elke keer dat deze functie word aangeroepen word er een volgend ledje aangezet
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
    
    int button1 = 0;
    int button2 = 0;
    int reset = 1;
	
	// main fase
	
    while (1)   {
		
		// loop om de lampjes aan en uit te zetten
        if (reset == 0)	{
			
			// onthouden dat knop 1 is ingedrukt
            if (buttonPress1 == 0)   {
                button1 = 1;
            }
        
			// onthouden dat knop 2 is ingedrukt
            if (buttonPress2 == 0)  {
                button2 = 1;
            }

			// als beide knoppen ingedrukt zijn geweest mag het lampje niet aangaan door het ingedrukt houden van het knopje,  hiermee verlaten we deze loop
            if (button1 == 1 && button2 == 1)   {
                reset = 1;
            }
        
			// als de knoppen beide niet, of wel zijn ingedrukt moet het looplicht
            if (button1 == button2)  {
                LATC = ledArray[3];
                button2 = 0;
                button1 = 0;
            }
			
			// als de knoppen ongelijk aan elkaar zijn moet het looplicht aan
            else {
                loopLicht();
            }
        }
        
		// loop om te zorgen dat er niet word gereageerd op het ingedrukt houden van de lampjes
        while (reset == 1)   {
            
			// als beide knoppen niet ingedrukt zijn gaat reset naar 0 zodat de lampjes weer aangezet kunnen worden
            if (buttonPress1 == 1 && buttonPress2 == 1) {
                reset = 0;
            }
        }
		
		// 
		__delay_ms(90);
    }
}
