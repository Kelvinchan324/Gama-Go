// This .cpp file contains the functions for GM tube, Dose rate function

#include <Arduino.h>
#include <stdint.h>
// #include <iostream>
// #include <numeric>

#include "0_Config.h"
#include "1_Global.h"

uint8_t GeigerCounts [] = {0,0,0,0,0,0,0,0,0,0,0,0};

float MinuteDoseRate;
int TotalCounts = 0;

// void beep()
// {
//   if ()
//   digitalWrite(BUZ,HIGH);
//   delay(5);
//   digitalWrite(BUZ,LOW);
// }

void GM_impulse ()
{
    //GM_Counts ++;
    GeigerCounts[CurrentCycle]++;
}

void GMinit ()
{
    pinMode (GMpin,INPUT);
    interrupts();
    // By default, interrupts are disabled in Arduino sketches to ensure precise timing and prevent unexpected behavior
    // The interrupts() function is called to enable interrupts globally after they have been disabled

    attachInterrupt(digitalPinToInterrupt(GMpin), GM_impulse, RISING);
}

void GetDoseRate ()
{   
    TotalCounts = 0;
    int GeigerArrayLength = sizeof(GeigerCounts) / sizeof(GeigerCounts[0]);
    for (byte n = 0; n < GeigerArrayLength; n++)
    {
        //Serial.print(geigerCounts[n]); Serial.print(" "); // for debugging
        TotalCounts += GeigerCounts[n];
    }
    // TotalCounts = std::reduce(cbegin(GeigerCounts), cend(GeigerCounts));

    GeigerCounts[CurrentCycle] = 0;

    if (millis() > (60 * 1000))
    {
        MinuteDoseRate = TotalCounts / (-0.0099 * TotalCounts + 103.22);
    //     if (TotalCounts > 102) //Dose rate > 0.3
    //     {                                  
    //         Sreen turns red 
    //     }
    //     else Screen turns black
    }

    else
    {
        MinuteDoseRate = ((12.0*(float)TotalCounts) / (CurrentCycle+1))/115;
    }
    

}