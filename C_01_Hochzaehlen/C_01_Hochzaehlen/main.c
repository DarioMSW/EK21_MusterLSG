/*
 * C_01_Hochzaehlen.c
 *
 * Created: 29.09.2022 11:29:00
 * Author : Milan
 */ 
#define F_CPU 16000000UL
#define MAX_NUMBER 65535 // 0...65535

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xFF;
    DDRB = 0XFF;
    while (1)
    {
        for (uint16_t i = 0; i <= MAX_NUMBER; i++)
        {
            PORTA = i;
            PORTB = i >> 8;
            _delay_ms(1000);
        }
    }
}

