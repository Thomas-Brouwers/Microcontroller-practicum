#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b11000000;			// AREF=2.56V, result left adjusted, ADC 0
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

int main( void )
{
	char str[80];
	init();
	DDRA = 0xFF;				// set PORTA for output
	DDRB = 0xFF;				// set PORTB for output
	adcInit();					// initialize ADC

	while (1)
	{
		set_cursor(0);
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		sprintf(str, "%d", ADCH);
		display_text(str);
		wait(100);				// every 100 ms (busy waiting)
	}
}