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

// declare functions
int _Analog_Digital_convertor_AN1(void);
int _Analog_Digital_convertor_AN9(void);

// declare global variables
char sendData = 0;

// macros

void putch (char c)
{
    while(TXSTA1bits.TRMT == 0);
    TXREG1 = c;
}

// see xc8 compiler documentation on why interrupts are named the way they are
void interrupt myIsr (void)	{
	
	// software interrupt
	// timer0 interrupting every 1 sec
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF)	{		// enables TMR0 overflow interrupt - TMR0 reached overflow?
		INTCONbits.TMR0IF = 0;							// reset TMR0, clears the overflow
		sendData = 1;
		// offset: 3036
		TMR0H = 0x5E;							// 94
		TMR0L = 0x1C;							// 28
	}
}

//low priority interrupts
void interrupt low_priority moreIsr (void)	{
	
	// interrupt becouse the ADC is done
	if (ADCON0bits.ADON && PIRbits.ADIF)	{
		PIRbits.ADIF = 0;								// reset ADC interrupt  
		;												// empty, this interrupt is supposed to happen inside the function that calls the ADC
	}
}

void main() {

	unsigned int value1;
	unsigned int value9;
	int valueTemp;
	int valueTemperatuur;

	// Ini fase
	
	// seriele communicatie
	TRISCbits.TRISC6 = 0;	// Tx1 output
	PIE3bits.RC2IE = 0;		// disable Rx interrupt USART2
	PIE3bits.TX2IE = 0;		// disable Tx interrupt USART2
	PIE1bits.RC1IE = 0;		// disable Rx interrupt USART1
	PIE1bits.TX1IE = 0;		// disable Tx interrupt USART1
	TXSTA1 = 0xA0;			//
	RCSTA1 = 0x80;			//
	BAUDCON1 = 0xC0;		//
	SPBRG1 = 12;			//  
	
	// Interrupts
	T0CON = 0b10000100;				// enables timer 1 as 16 bit with a /32 prescale
	INTCON2bits.TMR0IP = 1;			// overflow interrupt priority
	INTCONbits.TMR0IF = 0;			// clears the timer overflow
	INTCONbits.TMR0IE = 1;			// enables the timer interrupt	

	//loop om het de ADC uit te lezen en deze waarden weer te geven
    while(sendData == 1)
    {
        value1 = _Analog_Digital_convertor_AN1();
		value9 = _Analog_Digital_convertor_AN9();
		valueTemp = (value9 - 820)*10;
		valueTemperatuur = valueTemp / 4;
		if ((valueTemp % 4) >= 5)	{
			valueTemperatuur++;
		}
        printf("adcValue AN1 = %d, Temperatuur = %d.%02d\n\r", value1, (valueTemperatuur/100), (valueTemperatuur%100));
		sendData = 0;
    }
}

// functie om AN1 uit te lezen
int _Analog_Digital_convertor_AN1(void)
{
    ADCON0 = 0b00000111;       	//channel AN1[pin3](bit6-2), Start ADCconversion(bit1), ADC on(bit0)
    ADCON1 = 0b00110000;       	//trigger ECCP1(bit7-6), AVref 4.1V(bit5-4), AVss(bit3), Neg Channel00(AVss)(bit2-0)
    ADCON2 = 0b10110001;       	//right justified(bit7), Tad 16(bit5-3), conversion CLK Fosc/8(bit2-0)
	;							// put microcontroller to sleep
    while (ADCON0bits.nDONE == 1);
    return ADRESH << 8| ADRESL;
}

// functie om AN9 uit te lezen
int _Analog_Digital_convertor_AN9(void)
{
    ADCON0 = 0b00100111;       	//channel AN1[pin3](bit6-2), Start ADCconversion(bit1), ADC on(bit0)
    ADCON1 = 0b00110000;       	//trigger ECCP1(bit7-6), AVref 4.1V(bit5-4), AVss(bit3), Neg Channel00(AVss)(bit2-0)
    ADCON2 = 0b10110001;       	//right justified(bit7), Tad 16(bit5-3), conversion CLK Fosc/8(bit2-0)
	;							// put microcontroller to sleep
    while (ADCON0bits.nDONE == 1);
    return ADRESH << 8| ADRESL;
}