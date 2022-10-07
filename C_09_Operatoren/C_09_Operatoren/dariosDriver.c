/*
 * dariosDriver.c
 *
 * Created: 29.09.2022 14:08:07
 *  Author: Dario
 */ 


#include "dariosDriver.h"


void initBoard(void)
{
    //LEDs: Alle Bits auf Ausgang setzen
    DDRA=0xFF;
    DDRB=0xFF;
}

void ledWriteAll(uint16_t bitMuster)
{
    //LSB an PortA anzeigen
    PORTA = bitMuster;
    //MSB an PortB anzeigen
    PORTB = bitMuster >> 8;
}



void ledWrite(uint8_t ledNr0_15, uint8_t wert0_1)
{
    if (wert0_1)
    {
        ledWriteAll(ledReadALL() | ((uint16_t)1<<ledNr0_15));
    } 
    else
    {
        ledWriteAll(ledReadALL() & ~((uint16_t)1<<ledNr0_15));
    }
    
    
//     if (wert0_1)
//     {
//         //LED einschalten
//         PORTA = PORTA | (1<<ledNr0_15);
//         PORTB = PORTB | ((ledNr0_15>7)<<(ledNr0_15-8));
//     } 
//     else
//     {
//         //LED ausschalten
//         PORTA = PORTA & ~(1<<ledNr0_15);
//         PORTB = PORTB & ~((ledNr0_15>7)<<(ledNr0_15-8));
//        
}

uint16_t ledReadALL(void)
{
    return PORTA | ((uint16_t)(PORTB) << 8);
}



uint8_t switchRead(uint8_t switchNr0_7)
{
    return switchReadAll() & (1<<switchNr0_7);
}    

uint8_t switchReadAll(void)
{
    if (SWITCH_ACTIV_HIGH)
    {
        return PINC;
    }
    return ~PINC;
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

uint16_t adcRead(adcChannel_t kanal)
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



