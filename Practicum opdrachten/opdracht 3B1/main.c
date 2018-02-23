#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main( void )
{
	// Init I/O
	DDRD = 0xFF;

	init();
	

	set_cursor(5);
	display_text("Test");
		
	
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}