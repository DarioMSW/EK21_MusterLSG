/*
 * C06_Maskieren.c
 *
 * Created: 05.10.2022 13:45:12
 * Author : Milan
 */ 

#include <avr/io.h>


int main(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0x00;
    PORTC = 0xFF;
    PORTA = 0xFF;
    PORTB = 0xFF;
    while (1) 
    {
        if (PINC & 0x08)
        {
            PORTA |= 0x80;
        } 
        else
        {
            PORTA &= ~0x80;
        }
        if (PINC & 0x04)
        {
            PORTA &= ~0x40;
        }
        else
        {
            PORTA |= 0x40;
        }
        if (PINC & 0x02)
        {
            PORTA |= 0x03;
        }
        else
        {
            PORTA &= ~0x03;
        }
    }
}

