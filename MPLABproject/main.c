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

int _Analog_Digital_convertor_AN1(void);
int _Analog_Digital_convertor_AN9(void);

void putch (char c)
{
    while(TXSTA1bits.TRMT == 0);
    TXREG1 = c;
}

void main() {

	unsigned int value1;
	unsigned int value9;

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

	//loop om het de ADC uit te lezen en deze waarden weer te geven
    while(1)
    {
        value1 = _Analog_Digital_convertor_AN1();
		value9 = _Analog_Digital_convertor_AN9();		
        printf("adcValue AN1 = %d, adcValue AN9 = %d\n\r", value1, value9);
    }
}

// functie om AN1 uit te lezen
int _Analog_Digital_convertor_AN1(void)
{
    ADCON0 = 0b00000111;       //channel AN1[pin3](bit6-2), Start ADCconversion(bit1), ADC on(bit0)
    ADCON1 = 0b00110000;       //trigger ECCP1(bit7-6), AVref 4.1V(bit5-4), AVss(bit3), Neg Channel00(AVss)(bit2-0)
    ADCON2 = 0b10110001;       //right justified(bit7), Tad 16(bit5-3), conversion CLK Fosc/8(bit2-0)
    while ( ADCON0bits.nDONE == 1);
    return ADRESH << 8| ADRESL;
}

// functie om AN9 uit te lezen
int _Analog_Digital_convertor_AN9(void)
{
    ADCON0 = 0b00100111;       //channel AN1[pin3](bit6-2), Start ADCconversion(bit1), ADC on(bit0)
    ADCON1 = 0b00110000;       //trigger ECCP1(bit7-6), AVref 4.1V(bit5-4), AVss(bit3), Neg Channel00(AVss)(bit2-0)
    ADCON2 = 0b10110001;       //right justified(bit7), Tad 16(bit5-3), conversion CLK Fosc/8(bit2-0)
    while ( ADCON0bits.nDONE == 1);
    return ADRESH << 8| ADRESL;
}