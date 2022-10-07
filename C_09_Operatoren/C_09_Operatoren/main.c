/*
 * C_09_Operatoren.c
 *
 * Created: 07.10.2022 13:57:30
 * Author : Dario
 */ 

#include "dariosDriver.h"

#define IN_MASK_SCHALTER_7  0b10000000
#define IN_MASK_SCHALTER_6  0b01000000
#define IN_MASK_SCHALTER_5  0b00100000
#define IN_MASK_SCHALTER_4  0b00010000
#define IN_MASK_S1_S3       0b00001110

#define OFFSET_S1_S3        1


#define OUT_MASK_LED0       0b00000001
#define OUT_MASK_LED1       0b00000010
#define OUT_MASK_LED2       0b00000100
#define OUT_MASK_LED3       0b00001000


#define OFF                 0

int main(void)
{
    uint8_t inSchalter=0;
    uint8_t inSchalter7=0;
    uint8_t inSchalter6=0;
    uint8_t inSchalter5=0;
    uint8_t inSchalter4=0;
    uint8_t inWertS1_S3 = 0;
    uint8_t inWertS0_S7 = 0;
    
    uint8_t outLed0 = 0;
    uint8_t outLed1 = 0;
    uint8_t outLed2 = 0;
    uint8_t outLed3 = 0;
    
    
    
    /* Replace with your application code */
    while (1) 
    {
        //Eingabe
        inSchalter = switchReadAll();
        inSchalter7 = inSchalter & IN_MASK_SCHALTER_7;
        inSchalter6 = inSchalter & IN_MASK_SCHALTER_6;
        inSchalter5 = inSchalter & IN_MASK_SCHALTER_5;
        inSchalter4 = inSchalter & IN_MASK_SCHALTER_4;
        inWertS1_S3 = (inSchalter & IN_MASK_S1_S3) >> OFFSET_S1_S3;
        inWertS0_S7 = inSchalter;
        
        //Verarbeitung
        
        //Schalter 7 wird an Led 0 angezeigt.
        if (inSchalter7)
        {
            outLed0 = OUT_MASK_LED0;
        } 
        else
        {
            outLed0 = OFF;
        }
        
        //Wenn Schalter 7 und Schalter 6 aber nicht Schalter 5 aktiv ist, leuchtet LED 1, sonst nicht.
        if (inSchalter7 && inSchalter6 && (!inSchalter5))
        {
            outLed1 = OUT_MASK_LED1;
        } 
        else
        {
            outLed1 = OFF;
        }
        
        //Wenn Schalter 6, Schalter 5 oder Schalter 4 inaktiv ist, leuchtet LED 2, sonst nicht.
        //if (!(inSchalter6 && inSchalter5 && inSchalter4))
        if(!inSchalter6 || !inSchalter5 || !inSchalter4)
        {
            outLed2 = OUT_MASK_LED2;
        } 
        else
        {
            outLed2 = OFF;
        }
        
        //Wenn der Wert von Schalter 1-3(Schalter 1 ist LSB, Schalter 3 ist MSB)ungeradeist, leuchtet LED 3, sonst nicht.
        if (inWertS1_S3 % 2)
        {
            outLed3 = OUT_MASK_LED3;
        } 
        else
        {
            outLed3 = OFF;
        }
        
        
        //Ausgabe
        ledWriteAll(outLed0 | outLed1 | outLed2 | outLed3);
        
    }
}

