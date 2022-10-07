/*
* C_09_Operator.c
*
* Created: 6/10/2022 4:08:13 PM
* Author : Davide Della Vedova
*/

#include "DDV_Driver.h"



const uint8_t SWITCH0 = 0x01;
const uint8_t SWITCH1 = 0x02;
const uint8_t SWITCH2 = 0x04;
const uint8_t SWITCH3 = 0x08;
const uint8_t SWITCH4 = 0x10;
const uint8_t SWITCH5 = 0x20;
const uint8_t SWITCH6 = 0x40;
const uint8_t SWIT7 = 0x80;

int main(void)
{
    initBoard();
    
    uint8_t outLed0 = 0;
    uint8_t outLed1 = 0;
    uint8_t outLed2 = 0;
    uint8_t outLed3 = 0;
    uint8_t outLed4 = 0;
    uint8_t outLed5 = 0;
    uint8_t outLed6 = 0;
    uint8_t outLed7 = 0;
    
    uint8_t inSwitch = switchReadAll();
    
    while (1)
    {
        /*INPUT*/
        uint8_t inSwitch = switchReadAll();
        
        /*PROCESSSING*/
        if (inSwitch & SWIT7)                 // Wenn Schalter 7 und Schalter 6 aber nicht Schalter 5 aktiv ist, leuchtet LED 1, sonst nicht.
        {
            outLed0 = 0x01;
        }
        else
        {
            outLed0 = 0;
        }
        
        if (inSwitch & SWIT7 && inSwitch & SWITCH6)                           // Wenn Schalter 6, Schalter 5 oder Schalter 4 inaktiv ist, leuchtet LED 2, sonst nicht.
        {
            outLed1 = 0x02;
        }
        else
        {
            outLed1 = 0;
        }
        if (inSwitch & SWITCH5)                                                 //Wenn Schalter 7 und Schalter 6 aber nicht Schalter 5 aktiv ist, leuchtet LED 1, sonst nicht.
        {
            outLed1 = 0;
        }
        
        if (inSwitch & SWITCH6 && inSwitch & SWITCH5 && inSwitch & SWITCH4)     // Wenn Schalter 6, Schalter 5 oder Schalter 4 inaktiv ist, leuchtet LED 2, sonst nicht.
        {
            outLed2 = 0;
        }
        else
        {
            outLed2 = 0x04;
        }
        
        if (inSwitch & SWITCH1)                                                 // Wenn der Wert von Schalter 1-3(Schalter 1 ist LSB, Schalter 3 ist MSB)ungeradeist, leuchtet LED 3, sonst nicht.
        {
            outLed3 = 0x08;
        }
        else
        {
            outLed3 = 0;
        }
        
        if (inSwitch & SWITCH1)                                                 // Wenn der Wert von Schalter 1-3(Schalter 1 ist LSB, Schalter 3 ist MSB)geradeist, leuchtet LED 4, sonst nicht.
        {
            outLed4 = 0;
        }
        else
        {
            outLed4 = 0x10;
        }
        
        if (inSwitch % 17 == 0)                                                     // Wenn der Wert an Schalter 0 bis 7 (Schalter 0 ist LSB, Schalter 7 ist MSB) durch 17 teilbar ist, leuchtet LED 5, sonst nicht.
        {
            outLed5 = 0x20;
        }
        else
        {
            outLed5 = 0;
        }
        
        if (((inSwitch & SWITCH1 | inSwitch & SWITCH2 | inSwitch & SWITCH3) >> 1) > ((inSwitch & SWITCH4 | inSwitch & SWITCH5 | inSwitch & SWITCH6) >> 4)) // Wenn der Wert der Schalter 1-3(Schalter 1 ist LSB, Schalter 3 ist MSB)grösser ist als der Wert an Schalter4-6(Schalter 4ist LSB, Schalter 6ist MSB), leuchtet Led 6, sonst nicht.
        {
            outLed6 = 0x40;
        }
        else
        {
            outLed6 = 0;
        }
        if (((inSwitch & SWITCH1 | inSwitch & SWITCH2 | inSwitch & SWITCH3) >> 1) == ((inSwitch & SWITCH4 | inSwitch & SWITCH5 | inSwitch & SWITCH6) >> 4)) //Falls die beiden Werte gleich gross sind, leuchtet Led 7, sonst nicht.
        {
            outLed7 = 0x80;
        }
        else
        {
            outLed7 = 0;
        }
        
        /*OUTPUT*/
        if (inSwitch & SWITCH0)                                                     // Wenn Schalter 0 aktiv ist,soll die gesamte Ausgabe invertiert werden.
        {
            ledWriteAll(~(outLed0 | outLed1 | outLed2 | outLed3 | outLed4 | outLed5 | outLed6 | outLed7));
        }
        else
        {
            ledWriteAll(outLed0 | outLed1 | outLed2 | outLed3 | outLed4 | outLed5 | outLed6 | outLed7);
        }
    }
}

