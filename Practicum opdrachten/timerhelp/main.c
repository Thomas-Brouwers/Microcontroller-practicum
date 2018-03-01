// ********************************************************************************
// Includes
// ********************************************************************************
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

// ********************************************************************************
// Interrupt Routines
// ********************************************************************************
// timer1 overflow
ISR(TIMER1_OVF_vect) {
	// XOR PORTA with 0x02 to toggle the LSB
	PORTD=PORTD ^ 0x80;
}

// timer0 overflow
ISR(TIMER0_OVF_vect) {
	// XOR PORTA with 0x01 to toggle the second bit up
	PORTA=PORTA ^ 0x01;
}

// ********************************************************************************
// Main
// ********************************************************************************
int main( void ) {
	// Configure PORTA as output
	DDRD = 0xFF;
	// enable timer overflow interrupt for both Timer0 and Timer1
	TIMSK=(1<<TOIE0) | (1<<TOIE1);
	// start timer0 with /1024 prescaler
	TCCR0 = (1<<CS01);
	// lets turn on 16 bit timer1 also with /1024
	TCCR1B = (1 << CS12);
	// enable interrupts
	sei();
	while(1) {
	}
}