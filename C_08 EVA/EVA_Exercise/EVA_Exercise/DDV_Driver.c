/*
* DDV_Driver.c
*
* Created: 29/09/2022 2:21:17 PM
*  Author: Davide Della Vedova
*/

#include "DDV_Driver.h"

void initAdc(void);

void initBoard(void)
{
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0x00;
    PORTC = 0xff;
    initAdc();
}

void ledWriteAll(uint16_t bitMuster)
{
    PORTA = bitMuster;
    PORTB = bitMuster >> 8;
}

void ledWrite(uint8_t ledNr0_15, uint8_t wert0_1)
{
    if (wert0_1)
    {
        PORTA = PORTA | (1<<ledNr0_15);
        PORTB = PORTB | ((ledNr0_15>7)<<(ledNr0_15-8));
    }
    else
    {
        PORTA = PORTA & ~(1<<ledNr0_15);
        PORTB = PORTB & ~((ledNr0_15>7)<<(ledNr0_15-8));
    }
}

uint16_t ledReadAll(void)
{
    return PORTA | (uint16_t)PORTB << 8;
}

/** * \brief Liest die Schalter (PortC) ein * * \return uint8_t Eingestellter Schalterwert */
uint8_t switchReadAll(void)
{
    return ~PINC;
}


uint8_t switchRead(uint8_t switchNr0_7)
{
    return ~PINC & 1 << switchNr0_7;
}

void initAdc(void)
{
    //PORTF (ADC, X4) Eingang ohne PullUps
    PORTF   = 0x00;
    DDRF    = 0x00;
    //PORTK (ADC-Inputs) alles auf Eingang ohne Pullup
    PORTK   = 0x00;
    DDRK    = 0x00;
    
    ADMUX  = 0x40;    //AVCC Als referenz
    DIDR0  = 0x0F;    // Digitale Register an ADC pins der Potentiometer deaktivieren
    DIDR2  = 0xFF;
    
    ADCSRA = 0b10100111; // ADC einschalten, ADC clok = 16MHz / 128 --> 8us/cycle
    ADCSRB = 0x00;    // Free runing mode
    
    ADCSRA |=  0b01000000;        // Dummy messung Starten
    while((ADCSRA&0x10) == 0);    // Warten bis Messung abgeschllossen
    
    ADCSRA &= 0xEF;                // Interruptflage löschen
}

uint16_t adcRead(uint8_t kanal)
{
    uint16_t messwert = 0;
    
    // Kanal definieren
    ADMUX  = 0x40;    //AVCC Als referenz
    if(kanal>=8)
    {    ADMUX  |= kanal-8;
        ADCSRB |= (3 << MUX5);
    }
    else
    {    ADMUX  |= kanal;
        ADCSRB &= ~(3 << MUX5);
    }
    
    
    ADCSRA |=  0b01000000;        // ADC Starten
    while((ADCSRA&0x10) == 0);    // Warten bis Messung abgeschllossen
    
    _delay_us(300);//25 ADC clock cycles
    
    messwert = ADCL;
    messwert |= ADCH <<8;
    
    ADCSRA &= 0xEF;                // Interruptflage löschen
    
    return messwert;
}