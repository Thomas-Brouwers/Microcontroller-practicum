/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0x01, 100}, {0x02, 100}, {0x04, 100}, {0x08, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x81, 100}, {0x82, 100}, {0x84, 100}, {0x88, 100}, {0x90, 100}, {0xA0, 100}, {0xC0, 100},
	{0xC1, 100}, {0xC2, 100}, {0xC4, 100}, {0xC8, 100}, {0xD0, 100}, {0xE0, 100},
	{0xE1, 100}, {0xE2, 100}, {0xE4, 100}, {0xE8, 100}, {0xF0, 100},
	{0xF1, 100}, {0xF2, 100}, {0xF4, 100}, {0xF8, 100},
	{0xF9, 100}, {0xFA, 100}, {0xFC, 100}, 
	{0xFD, 100}, {0xFE, 100}, 
	{0xFF, 100}, 
	{0x00, 100}, 
	{0xFF, 100},
	{0x00, 100},
	{0xFF, 100}, {0xE7, 100}, {0xC3, 100}, {0x81, 100}, {0x00, 100},
	{0x00, 0x00}
	};

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


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	DDRD = 0b11111111;					// PORTD all output 
	
	while (1==1)
	{
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD	
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}

	return 1;
}