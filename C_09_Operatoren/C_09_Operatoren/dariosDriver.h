/*
 * dariosDriver.h
 *
 * Created: 29.09.2022 14:08:46
 *  Author: Dario
 */ 


#ifndef DARIOSDRIVER_H_
#define DARIOSDRIVER_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>




/**
 * \brief Initialisiert das uC-Board
 * 
 * \param 
 * 
 * \return void
 */
void initBoard (void);

/**
 * \brief Zeigt ein Bitmuster an den LEDs an
 * 
 * \param bitMuster     Das Bitmuster, das angezeigt werden soll
 * 
 * \return void
 */
void ledWriteAll (uint16_t bitMuster);


/**
 * \brief Setzt eine einzelne LED
 * 
 * \param ledNr0_15 Welche LED soll gesetzt werden? LED 0 = PORTA Bit 0 und LED 15 = PORTB Bit 7
 * \param wer0_1 Auf welchen Wert soll die LED gesetzt werden? 1 = LED leuchtet
 */
void ledWrite(uint8_t ledNr0_15, uint8_t wert0_1);



/**
 * \brief Gibt zurück, was im Moment an den LEDs angezeigt wird  (PortA0 LSB bis PortB7 MSB)
 *
 * \return uint16_t Bitmuster, das an den LEDs angezeigt wird
 */
uint16_t ledReadALL(void);




/**
 * \brief Gibt an ob die Schalter (PortC) aktiv High oder Low sind (default: 1)
 */
#define SWITCH_ACTIV_HIGH   0

/**
 * \brief Liest die Schalter (PortC) ein
 *
 * \return uint8_t Eingestellter Schalterwert
 */
uint8_t switchReadAll(void);

/**
 * \brief Liest einen einzelnen Schalter ein.
 * 
 * \param switchNr0_7 Welcher Schalter soll eingelesen werden?
 *                    Schalter 0 = PORTC Bit 0 / Schalter 7 = PORTC Bit 7
 * 
 * \return uint8_t Wahr wenn der Schalter ein ist, falsch wenn der Schalter aus ist.
 */
uint8_t switchRead(uint8_t switchNr0_7);








// Alle Analog-Eingänge und ihre Funktionen
typedef enum adcChannel_t {
    ADC_00_X4_PORTF_BIT0 = 0,   //Anschluss X4
    ADC_01_X4_PORTF_BIT1,       //Anschluss X4
    ADC_02_X4_PORTF_BIT2,       //Anschluss X4
    ADC_03_X4_PORTF_BIT3,       //Anschluss X4
    ADC_04_NOT_USED,            //Nicht in Gebrauch
    ADC_05_NOT_USED,            //Nicht in Gebrauch
    ADC_06_NOT_USED,            //Nicht in Gebrauch
    ADC_07_NOT_USED,            //Nicht in Gebrauch
    ADC_08_POTI_1,              //Board: Potentiometer 1 (PK0, R1)
    ADC_09_POTI_2,              //Board: Potentiometer 2 (PK1, R6)
    ADC_10_JOYSTICK_X,          //Board: Joystick X (PK2)
    ADC_11_JOYSTICK_Y,          //Board: Joystick Y (PK3)
    ADC_12_LICHT,               //Board: Sichtsensor (PK4)
    ADC_13_TEMPERATUR,          //Board: Temperatursensor (PK5)
    ADC_14_MAGNET_1,            //Board: Magnetsensor 1 (PK6, IC3)
    ADC_15_MAGNET_2             //Board: Magnetsensor 2 (PK6, IC4)
    } adcChannel_t;

/**
 * \brief Liest einen Analogen Wert von einem ADC ein. Auflösung 10 Bit (0..1023)
 * 
 * \param kanal Einen ADC-Kanal, siehe adcChannel_t
 * 
 * \return uint16_t Eingelesener 10 Bit Wert zwischen 0...1023
 */
uint16_t adcRead(adcChannel_t kanal);


#endif /* DARIOSDRIVER_H_ */