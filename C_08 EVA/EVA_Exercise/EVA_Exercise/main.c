/*
* EVA_Exercise.c
*
* Created: 6/10/2022 7:48:02 AM
* Author : Davide Della Vedova
*/

#include "DDV_Driver.h"
#define IN_MASK_WOHNZIMMER 0b00000001
#define IN_MASK_BAD 0b00000100
#define IN_MASK_1OG 0b00010000
#define IN_MASK_2OG 0b00100000
#define IN_MASK_EG 0b01000000
#define IN_MASK_LICHTSENS 0b10000000
#define OUT_MASK_WOHNZIMMER 0b00000001
#define OUT_MASK_BAD 0b00000010
#define OUT_MASK_SPIEGEL 0b00000100
#define OUT_MASK_EG 0b01000000
#define OUT_MASK_OG 0b10000000
#define OFF 0


int main(void)
{
    /*INITIALIZING*/
    initBoard();
    
    uint8_t inWohnzimmer    = 0;
    uint8_t inBad           = 0;
    uint8_t in1Og           = 0;
    uint8_t in2Og           = 0;
    uint8_t inEg            = 0;
    uint8_t inLichtSens     = 0;
    
    uint8_t outWohnzimmer   = 0;
    uint8_t outBad          = 0;
    uint8_t OutTreppe       = 0;
    
    while (1)
    {
        /*INPUT*/
        uint8_t inSwitch = switchReadAll();
        
        inWohnzimmer = inSwitch & IN_MASK_WOHNZIMMER;
        inBad = inSwitch & IN_MASK_BAD;
        in1Og = inSwitch & IN_MASK_1OG;
        in2Og = inSwitch & IN_MASK_2OG;
        inEg = inSwitch & IN_MASK_EG;
        inLichtSens = inSwitch & IN_MASK_LICHTSENS;
        
        /*PROCESSING*/
        if (inWohnzimmer)
        {
            outWohnzimmer = OUT_MASK_WOHNZIMMER;
        }
        else
        {
            outWohnzimmer= OFF;
        }
        
        if (inBad)
        {
            outBad = OUT_MASK_BAD | OUT_MASK_SPIEGEL;
        }
        else
        {
            outBad = OFF;
        }
        
        if ((in1Og||in2Og||inEg))
        {
            OutTreppe = OUT_MASK_EG | OUT_MASK_OG;
        }
        else
        {
            OutTreppe = OFF;
        }
        if (inLichtSens)
        {
            OutTreppe = OFF;
        }
        
        /*OUTPUT*/
        ledWriteAll(outWohnzimmer | outBad | OutTreppe);
    }
}

