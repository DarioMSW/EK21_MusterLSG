/*
 * DDV_Driver.h
 *
 * Created: 29/09/2022 2:21:37 PM
 *  Author: Davide Della Vedova
 *https://github.com/DavideDellaVedova/MSW_C_Exercises/blob/main/Treiber/DDV_Driver/DDV_Driver/DDV_Driver.h
 */ 


#ifndef DDV_DRIVER_H_
#define DDV_DRIVER_H_

#define __DELAY_BACKWARD_COMPATIBLE__ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>




/**
 * \brief sets all LED Outputs to high
 * 
 * \param 
 * 
 * \return void
 */
void initBoard(void);

/**
 * \brief displays a bit Pattern on the LEDs
 * 
 * \param bitMuster
 * 
 * \return void
 */
void ledWriteAll(uint16_t bitMuster);


void ledWrite(uint8_t ledNr0_15, uint8_t wert0_1);


uint16_t ledReadAll(void);


uint8_t switchReadAll(void);


uint8_t switchRead(uint8_t switchNr0_7);

/**
 * \brief Liest einen Analogen Wert von einem ADC ein. Auflösung 10 Bit (0..1023)
 * 
 * \param kanal Einen ADC-Kanal, siehe adcChannel_t
 * 
 * \return uint16_t Eingelesener 10 Bit Wert zwischen 0...1023
 */
uint16_t adcRead(uint8_t kanal);



#endif /* DDV_DRIVER_H_ */