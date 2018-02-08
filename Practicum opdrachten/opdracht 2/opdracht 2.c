/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** knipper.c
**
** Beschrijving:	Read input (switch) on PORTD.7 and show status on PORTD.0
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o switch.elf switch.o
**					avr-objcopy -O ihex switch.elf switch.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	// set PORTD for output
	DDRD = 0b11111111;					// PORTD.7 input all other bits output
	//PORTC = 0x10;						// ??
	
	while (1)
	{
		
		if(PINC & 0x01)
		{
							// write 0 to all the bits of PortD
			PORTD = 0x80;			// Write 10000000b PORTD
			wait( 500 );
			PORTD = 0x00;
			wait( 500 );
		}
		else
		{
			PORTD = 0x00;			// write 1 to all the bits of PortD
		}
	}

	return 1;
}