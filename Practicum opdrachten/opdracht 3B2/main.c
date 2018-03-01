#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int tenthValue = 0;
int CompareValue = 0;

// Interrupt routine timer2 overflow
//
ISR( TIMER2_OVF_vect )
{
	tenthValue++; // Increment counter
}
// Initialize timer2
//
void timer2Init( void )
{
	OCR2 = CompareValue; // Compare value of counter 2
	TIMSK |= 0x08; // T2 compare match interrupt enable
	SREG |= 0x08; // turn_on intr all
	TCCR2 = 0b00011111; // Initialize T2: ext.counting, rising edge
	// compare output mode, CTC, RUN
}

// Main program: Counting on T2
int main( void )
{
	char str[80];
	init();
	DDRD &= 0b00000010; // set PORTD.7 for input
	DDRA = 0xFF; // set PORTB for output (shows countregister)
	DDRB = 0xFF; // set PORTC for output (shows tenth value)
	timer2Init();
	while (1)
	{
		PORTA = TCNT2; // show value counter 2
		PORTB = tenthValue; // show value tenth counter
		sprintf(str, "%d", TCNT2);
		display_text(str);
		set_cursor(0);
		wait(10); // every 10 ms
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
