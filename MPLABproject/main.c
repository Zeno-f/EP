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
}