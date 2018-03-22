/*
 * lcd.h
 *
 * Created: 23-2-2018 10:48:42
 *  Author: tmbro
 */ 


#ifndef LCD_H_
#define LCD_H_

void init(void);
void display_text(char *str);
void set_cursor(int position);
void lcd_write_data(unsigned char byte);
void lcd_strobe_lcd_e(void);




#endif /* LCD_H_ */