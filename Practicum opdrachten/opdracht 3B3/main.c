/*
 * opdracht 3B3.c
 *
 * Created: 23-2-2018 13:47:59
 * Author : tmbro
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int msCount = 0;

// Interrupt routine timer2 overflow
//
ISR( TIMER2_COMP_vect )
{
	msCount++; // Increment ms counter
	if ( msCount == 500 )
	{
		PORTC ^= BIT(0); // Toggle bit 0 van PORTC
		msCount = 0; // Reset ms_count value
	}
}
// Initialize timer2
//
void timer2Init( void )
{
	OCR2 = 250; // Compare value of counter 2
	TIMSK |= 0x07; // T2 compare match interrupt enable
	SREG |= 0x07; // turn_on intr all
	TCCR2 = 0b00011111; // Initialize T2: ext.counting, rising edge
	// compare output mode, CTC, RUN
}

// Main program: Counting on T2
int main( void )
{
	DDRC = 0xFF; // set PORTC for output (toggle PC0)
	timer2Init();
	while (1)
	{
		// do something else
		wait(10); // every 10 ms (busy waiting
	}
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
