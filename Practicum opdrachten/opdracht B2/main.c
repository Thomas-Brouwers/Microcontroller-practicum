/*
 * opdracht B2.c
 *
 * Created: 8-2-2018 16:25:32
 * Author : tmbro
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int index = 0;

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
ISR( INT0_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTD = pattern[index].data;
	// wait
	wait(pattern[index].delay);
	// increment for next round
	index++;	
}

/******************************************************************/
ISR( INT1_vect )
/*
short:			ISR INT2
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTD = pattern[index].data;
	// wait
	wait(pattern[index].delay);
	// increment for next round
	index++;
}

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

int main(void)
{
	DDRD = 0xFC;
	//PORTD = 0x01;
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

