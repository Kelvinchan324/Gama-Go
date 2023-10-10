// This .cpp file contains the functions for BMP function
#include <Adafruit_BMP085.h>  //Include library for BMP180

#include "0_Config.h"
#include "1_Global.h"

Adafruit_BMP085 bmp;       //Setting BMP object

float BMPpressure;


void bmpInit()
{
    bmp.begin();
}

void GetBMPevent()
{
    BMPpressure = -99.99;
    BMPpressure = bmp.readPressure()*0.01;

    stnP[CurrentCycle] = BMPpressure;


}