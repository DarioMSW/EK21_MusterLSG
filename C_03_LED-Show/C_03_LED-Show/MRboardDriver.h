/*
 * MRboardDriver.h
 *
 * Created: 29.09.2022 14:25:09
 *  Author: Milan
 */ 


#ifndef MRBOARDDRIVER_H_
#define MRBOARDDRIVER_H_
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>


void initBoard(void);
/**
 * \brief Initialisiert das uC-Board
 *
 * \param
 *
 * \return void
 */


void ledWriteAll(uint16_t bitMuster);
/**
 * \brief Initialisiert das uC-Board
 *
 * \param bitMuster = 16 bit Wert
 *
 * \return void
 */


void ledWrite(uint8_t ledNr, uint8_t state);
/**
 * \brief Initialisiert das uC-Board
 *
 * \param ledNr 0-15, State 0-1
 *
 * \return void
 */


uint16_t ledReadAll(void);
/**
 * \brief Liest zustand des LEDs
 *
 * \param   
 *
 * \return 16 bit unsigned integer
 */

uint8_t switchRead(uint8_t switchNr);
/**
 * \brief Liest zustand des switchNr Schalters
 *
 * \param Schalter Nummer
 *
 * \return 8 bit 0 oder 1 wert
 */

uint8_t switchReadAll(void);
/**
 * \brief Liest zustand des Schalters
 *
 * \param 
 *
 * \return 8 bit muster
 */





#endif /* MRBOARDDRIVER_H_ */