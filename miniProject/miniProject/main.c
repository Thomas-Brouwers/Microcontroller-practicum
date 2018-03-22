#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void InitADC()
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!

	ADCSRA|=(1<<ADIF);

	return(ADC);
}

void Wait()
{
	uint8_t i;
	for(i=0;i<20;i++)
	_delay_loop_2(0);
}

int main( void)
{
	DDRB = 0b11111111;	
	char str[80];
	uint16_t adc_result;
	init();
	//Initialize ADC
	InitADC();
	PORTB= 0x00; 
	while(1)
	{
		sprintf(str, "%s", "   ");
		display_text(str);
		set_cursor(0);
		adc_result=ReadADC(0);           // Read Analog value from channel-0
		sprintf(str, "%d", adc_result);
		display_text(str);
		set_cursor(0);
		if(PINA == 0x01){
			if(adc_result < 10){
				PORTB = adc_result % 7 + 1;
				_delay_ms(100);
			} else {
			PORTB = 0x00;
			_delay_ms(100);
		}
		} else {
			PORTB= 0x00;
			_delay_ms(100);
		}
		_delay_ms(250);
	}
	return 1;
}
