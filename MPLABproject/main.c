/*
 *	Embedded Programming 2018
 *
 *	Opdracht: ADC
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

int Analog_Digital_convertor(void);

void putch (char c)
{
    while(TXSTA1bits.TRMT == 0);
    TXREG1 = c;
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
	
	ANCON0.ANSEL1 = 1;
    ANCON1.ANSEL9 = 1;
    
    while(1)
    {
        value = _Analog_Digital_convertor();
        printf("adcValue = %d\n\r", value);
    }
	
	int Analog_Digital_convertor(void)
    {
        ADCON0 = 00100111;       //channel AN1[pin3](bit6-2), Start ADCconversion(bit1), ADC on(bit0)
        ADCON1 = 00000010;       //trigger ECCP1(bit7-6), AVdd(bit5-4), AVss(bit3), Neg Channel00(AVss)(bit2-0)
        ADCON2 = 10110001;       //right justified(bit7), Tad 0(bit5-3), conversion CLK Fosc/2(bit2-0)
        while ( ADCON0bits.bit1 == 1);
        return ADRESH << 8| ADRESL;
    }

}