/*
 * MRboardDrivert.c
 *
 * Created: 29.09.2022 14:25:20
 *  Author: Milan
 */ 
#include "MRboardDriver.h"

void initBoard(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0x00;
    PORTC = 0xFF;    
}

void ledWriteAll(uint16_t bitMuster)
{
    PORTA = bitMuster;
    PORTB = bitMuster >> 8;
}

void ledWrite(uint8_t ledNr, uint8_t state)
{
    if (state)
    {
        PORTA |= (0x01 << ledNr);
        PORTB |= ((ledNr>7) << (ledNr - 8));
    } 
    else
    {
        PORTA &= ~(1 << ledNr);
        PORTB &= ~((ledNr>7) << (ledNr - 8));   
    }
}

uint16_t ledReadAll(void)
{
    return PORTA | ((uint16_t)PORTB << 8);
}

uint8_t switchRead(uint8_t switchNr)
{
    return PINC & (1<<switchNr);
}

uint8_t switchReadAll(void)
{
    return PINC;
}