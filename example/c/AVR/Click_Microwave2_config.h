#include "Click_Microwave2_types.h"

const uint32_t _MICROWAVE2_UART_CFG [ 3 ] = 
{
        9600, 
        _UART_NOPARITY, 
        _UART_ONE_STOPBIT
};
// LCD module connections
sbit LCD_RS at PORTA2_bit;
sbit LCD_EN at PORTD6_bit;
sbit LCD_D4 at PORTC4_bit;
sbit LCD_D5 at PORTC5_bit;
sbit LCD_D6 at PORTC6_bit;
sbit LCD_D7 at PORTC7_bit;

sbit LCD_RS_Direction at DDA2_bit;
sbit LCD_EN_Direction at DDD6_bit;
sbit LCD_D4_Direction at DDC4_bit;
sbit LCD_D5_Direction at DDC5_bit;
sbit LCD_D6_Direction at DDC6_bit;
sbit LCD_D7_Direction at DDC7_bit;
// End LCD module connections