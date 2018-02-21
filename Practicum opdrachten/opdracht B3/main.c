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
#include <avr/interrupt.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 
int idx = 0;


// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

PATTERN_STRUCT pattern[] = { 
	{0x80, 150}, {0x00, 150}, 
	{0x80, 150}, {0x00, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x00, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},	
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x00, 150},
	{0xFF, 0}
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

ISR( INT0_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	idx++;
	
}
ISR( INT1_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	idx--;
	
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
	DDRD = 0xFC;
	DDRC = 0XFF;
	//PORTD = 0x01;
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0			
	
	sei();
	while (1==1)
	{
		wait(100);
		switch(idx){
			case 0: PORTC = 0b0111111; break;
			case 1: PORTC = 0b0000110; break;
			case 2: PORTC = 0b1011011; break;
			case 3: PORTC = 0b1001111; break;
			case 4: PORTC = 0b1100110; break;
			case 5: PORTC = 0b1101101; break;
			case 6: PORTC = 0b1111101; break;
			case 7: PORTC = 0b0000111; break;
			case 8: PORTC = 0b1111111; break;
			case 9: PORTC = 0b1101111; break;
			case 10: PORTC = 0b1110111; break;
			case 11: PORTC = 0b1111100; break;
			case 12: PORTC = 0b0111001; break;
			case 13: PORTC = 0b1011110; break;
			case 14: PORTC = 0b1111001; break;
			case 15: PORTC = 0b1110001; break;
			case 16: PORTC = 0b1111001; break;
		}
		
	}

	return 1;
}