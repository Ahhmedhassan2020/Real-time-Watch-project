/*
 * Real time clock.c
 *
 * Created: 1/2/2023 11:26:19 AM
 * Author : Ahmed Hassan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "timers.h"
#include "Keypad.h"
#include "seven segment.h"
#include "std_macros.h"
volatile unsigned char seconds_counter=0;//to configure seconds of clock
/*to configure minutes and hours of clock*/
unsigned char minutes_counter , hours_counter;
unsigned char value,First_digit,Seconed_digit;
int main(void)
{
	/*initialize LCD*/
	LCD_intial();
	/*initialize keypad*/
	keypad_vInit();
	/*initialize Seven segment*/
	seven_seg_init('B');
	/*to apply Multplixing Technique*/
	SET_BIT(DDRC,0);//E1
	SET_BIT(DDRC,1);//E2
	SET_BIT(DDRC,2);//E3
	SET_BIT(DDRC,3);//E4
	SET_BIT(DDRC,4);//E5
	SET_BIT(DDRC,5);//E6
	/*to configure LCD*/
    LCD_send_string("press 1 to");
	LCD_move_cursor(2,1);
	LCD_send_string("set clock");
	/*initialize timer2*/
	timer2_overflow_init_interrupt();
    while (1) 
    {
		value = keypad_u8check_press();
		if (value!=NOTPRESSED)
		{
			if (value=='1')
			{
				LCD_clear_screen();
				LCD_send_string("Hours=--");
				LCD_move_cursor(1,7);
				_delay_ms(500);
				do 
				{
					First_digit = keypad_u8check_press();
					
				} while (First_digit==NOTPRESSED);
				LCD_send_char(First_digit);
				_delay_ms(300);
				do
				{
					Seconed_digit = keypad_u8check_press();
					
				} while (Seconed_digit==NOTPRESSED);
				LCD_send_char(Seconed_digit);
				_delay_ms(300);
				hours_counter = ((Seconed_digit-48)+10*(First_digit-48));
				LCD_clear_screen();
				LCD_send_string("minutes=--");
				LCD_move_cursor(1,9);
				_delay_ms(500);
				do
				{
					First_digit = keypad_u8check_press();
					
				} while (First_digit==NOTPRESSED);
				LCD_send_char(First_digit);
				_delay_ms(300);
				do
				{
					Seconed_digit = keypad_u8check_press();
					
				} while (Seconed_digit==NOTPRESSED);
				LCD_send_char(Seconed_digit);
				_delay_ms(300);
				minutes_counter = ((Seconed_digit-48)+10*(First_digit-48));
				LCD_clear_screen();
				LCD_send_string("seconds=--");
				LCD_move_cursor(1,9);
				_delay_ms(500);
				do
				{
					First_digit = keypad_u8check_press();
					
				} while (First_digit==NOTPRESSED);
				LCD_send_char(First_digit);
				_delay_ms(300);
				do
				{
					Seconed_digit = keypad_u8check_press();
					
				} while (Seconed_digit==NOTPRESSED);
				LCD_send_char(Seconed_digit);
				_delay_ms(300);
				seconds_counter = ((Seconed_digit-48)+10*(First_digit-48));
				LCD_clear_screen();
				LCD_send_string("press 1 to");
				LCD_move_cursor(2,1);
				LCD_send_string("set clock");
			}
			else{
				LCD_clear_screen();
				LCD_send_string("wrong choice");
				_delay_ms(1000);
				LCD_clear_screen();
				LCD_send_string("press 1 to");
				LCD_move_cursor(2,1);
				LCD_send_string("set clock");
				}
			}
			
		CLR_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		seven_seg_write('B',seconds_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		CLR_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		seven_seg_write('B',seconds_counter/10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		CLR_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		seven_seg_write('B',minutes_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		CLR_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		seven_seg_write('B',minutes_counter/10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		CLR_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		seven_seg_write('B',hours_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		CLR_BIT(PORTC,5);
		seven_seg_write('B',hours_counter/10);
		_delay_ms(5);
		if (seconds_counter==60)
		{
			seconds_counter = 0;
			minutes_counter++;
		}
		if (minutes_counter==60)
		{
			minutes_counter = 0;
			hours_counter++;
		}
		if (hours_counter==24)
		{
			seconds_counter = 0;
		}
				
	}
}
ISR(TIMER2_OVF_vect)
{
	seconds_counter++;
}