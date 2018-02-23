/*
 * lcd.c
 *
 * Created: 23-2-2018 10:48:57
 *  Author: tmbro
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void init(void)
/*
short:			Init LCD module in 4 bits mode.
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}

void display_text(char *str)
/*
short:			Writes string to LCD at cursor position
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// Het kan met een while:

	// while(*str) {
	// 	lcd_write_data(*str++);
	// }

	// of met een for:
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void set_cursor(int position)
{
	//for (int i = 0; i<position;i++){
	lcd_command(0x80 + position);
	//}
}

void lcd_write_data(unsigned char byte)
/*
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_strobe_lcd_e(void)
/*
short:			Strobe LCD module E pin --__
inputs:
outputs:
notes:			According datasheet HD44780
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void lcd_command ( unsigned char dat )
{
	PORTC = dat & 0xF0; // hoge nibble
	PORTC = PORTC | 0x08; // data (RS=0),
	// start (EN=1)
	_delay_ms(1); // wait 1 ms
	PORTC = 0x04; // stop (EN = 0)
	PORTC = (dat & 0x0F) << 4; // lage nibble
	PORTC = PORTC | 0x08; // data (RS=0),
	// start (EN=1)
	_delay_ms(1); // wait 1 ms
	PORTC = 0x00; // stop
	// (EN=0 RS=0)
}