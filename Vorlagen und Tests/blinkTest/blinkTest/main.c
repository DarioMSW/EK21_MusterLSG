/*
 * blinkTest.c
 *
 * Created: 09.11.2022 13:03:22
 * Author : Dario
 */ 

#include <avr/io.h>

#include "dariosDriver.h"

#define PROGRAMMTAKT_ms         10

#define ON_TIME_WARNBLINKER_ms  500
#define OFF_TIME_WARNBLINKER_ms 500
#define PERIODE_WARNBLINKER_ms  (ON_TIME_WARNBLINKER_ms+OFF_TIME_WARNBLINKER_ms)

#define ON_TIME_POWERBLINK_ms   100
#define OFF_TIME_POWERBLINK_ms  100
#define PERIODE_POWERBLINK_ms   (ON_TIME_POWERBLINK_ms+OFF_TIME_POWERBLINK_ms)

#define IN_MASKE_POWER          0x01
#define OUT_MASKE_WARN_LEDS     0xfffe
#define OUT_MASKE_POWER         0x0001


int main(void)
{
    uint8_t inSchalter = 0;
    uint8_t inPower = 0;
    uint8_t flagWarnBlinkerEin = 0;
    uint8_t flagPowerBlinkerEin = 0;
    uint16_t outWarnLeds = 0;
    uint16_t outPower = 0;
    uint16_t timerWarnblinker_ms = 0;
    uint16_t timerPowerblinker_ms = 0;
    
    initBoard();
    

    /* Replace with your application code */
    while (1) 
    {
        //Eingabe
        inSchalter = switchReadAll();
        inPower = inSchalter & IN_MASKE_POWER;
        
        //Verarbeitung
        if (inPower)
        {
            //Blinken aktivieren
            flagPowerBlinkerEin = 1;
            flagWarnBlinkerEin = 1;
        } 
        else
        {
            //Blinken deaktivieren und LEDs ausschalten
            flagPowerBlinkerEin = 0;
            outPower = 0;
            flagWarnBlinkerEin = 0;
            outWarnLeds = 0;
        }
        
        //Ausgabe
        //Warnblinker
        if (flagWarnBlinkerEin)
        {
            if ((timerWarnblinker_ms == 0) || (timerWarnblinker_ms >= PERIODE_WARNBLINKER_ms))
            {
                outWarnLeds = OUT_MASKE_WARN_LEDS;
                timerWarnblinker_ms=0;
            }else if (timerWarnblinker_ms >= ON_TIME_WARNBLINKER_ms)
            {
                outWarnLeds = 0;
            }
        }else{
            //Timer auf Periodenende setzen -> nächster Blinkstart werden
            //LEDs sofort eingeschaltet
            timerWarnblinker_ms = PERIODE_WARNBLINKER_ms;
        }
        
        //Powerblinker
        if (flagPowerBlinkerEin)
        {
            if ((timerPowerblinker_ms == 0) || (timerPowerblinker_ms >= PERIODE_POWERBLINK_ms))
            {
                outPower = OUT_MASKE_POWER;
                timerPowerblinker_ms=0;
            }else if (timerPowerblinker_ms >= ON_TIME_POWERBLINK_ms)
            {
                outPower = 0;
            }
        }else{
            //Timer auf Periodenende setzen -> nächster Blinkstart werden
            //LEDs sofort eingeschaltet
            timerPowerblinker_ms = PERIODE_POWERBLINK_ms;
        }
        
        ledWriteAll(outWarnLeds | outPower);
        
        //Programmtakt
        _delay_ms(PROGRAMMTAKT_ms);
        timerWarnblinker_ms = timerWarnblinker_ms + PROGRAMMTAKT_ms;
        timerPowerblinker_ms = timerPowerblinker_ms + PROGRAMMTAKT_ms;
        
    }
    
}










