/*
 * C_03_LED-Show.c
 *
 * Created: 30.09.2022 08:48:26
 * Author : Milan
 */ 

#include "MRboardDriver.h"
#define ANZAHL_LEDS 16

void lauflicht(uint16_t delay_ms);
void lauflichtRL(uint16_t delay);
void lauflichtFull(uint16_t delay);
void lauflichtFullR(uint16_t delay);
void ladeBalken(uint16_t maxWert, uint16_t aktWert);

int main(void)
{
    initBoard();
    while (1) 
    {
    }
}

void lauflicht(uint16_t delay_ms)
{
    for (uint8_t i = 0; i < 15; i++)
    {
        _delay_ms(delay_ms);
        ledWriteAll(1<<i);
        
    }
}

void lauflichtRL(uint16_t delay)
{
    for (uint8_t i = 0; i < 15; i++)
    {
        _delay_ms(delay);
        ledWriteAll(1<<(i+1));
        
    }
    for (uint8_t i = 0; i < 16; i++)
    {
        _delay_ms(delay);
        ledWriteAll(1<<(14-i));
        
    }
}

void lauflichtFull(uint16_t delay)
{
    uint16_t bitMuster = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        ledWriteAll(bitMuster);
        bitMuster |= 1<<i;
        _delay_ms(delay);
    }
}

void lauflichtFullR(uint16_t delay)
{
    uint16_t bitMuster = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        ledWriteAll(bitMuster);
        bitMuster |= 1<<i;
        _delay_ms(delay);
    }
    for (uint8_t i = 0; i < 16; i++)
    {
        ledWriteAll(bitMuster);
        bitMuster &= ~(1<<i);
        _delay_ms(delay);
    }
}

void ladeBalken(uint16_t maxWert, uint16_t aktWert)
{
    ledWriteAll(0xFFFF>>(ANZAHL_LEDS-(uint32_t)ANZAHL_LEDS*aktWert/maxWert)); //*100000 für genauigkeit
}