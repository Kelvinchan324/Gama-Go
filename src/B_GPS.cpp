// This .cpp file contains the functions for GPS function

#include <TinyGPS++.h>       //Include the library for GPS
#include <SoftwareSerial.h> //Include the library for creating extra UART pins for communication

#include <TFT_eSPI.h>         //Include library for SPI TFT display
#include <TFT_eWidget.h>      //Include library for TFT buttons

#include "0_Config.h"         // Include header file for Pin configuration
#include "1_Global.h"              // Include header file for Global variables

TinyGPSPlus gps;  //Set the TinyGPS++ object
SoftwareSerial gpsSerial (GPSTX,GPSRX);

double gpsLat, gpsLng, gpsAlt;
double gpsNum;
char gpsTime[12], gpsDate[12];
char GPS_dateString[10];
char GPS_timeString[10];

void gpsInit()
{
    gpsSerial.begin(9600);  // This line of code opens the gps communication channel

}

void getGPS()
{
// Init. the variables used in this function ---------//
    char _inchar;
    int GPScount = 0;
    unsigned long _start = millis();
//----------------------------------------------------//
    gpsSerial.listen();

    while(gpsSerial.available()) gpsSerial.read(); //Flushing buffer
    //delay(1000);

    while (millis() - _start <= 1000)
    {
        while (gpsSerial.available())
        {
            char gpsData = gpsSerial.read();
            //Serial.print(gpsData);
            gps.encode(gpsData);
        }
    }
    
    

}

void PrintGPSstring()
{

// Encoding the GPS date String ------------------------------------------------------------------------------------------------//
    if (gps.date.isValid()) //If we can get the date from the GPS module then we are going to print it
    {
        sprintf(GPS_dateString,"%02d/%02d/%02d", gps.date.day(), gps.date.month(), gps.date.year()%100);
        sprintf(gpsDate,"%02d%02d%04d", gps.date.day(), gps.date.month(), gps.date.year());
        //Here we print the Date,Month, and Year we get from the GPS module into the GPS_charString
        // sprintf is a function called string print format, in which the first item is the place where we put the string
        //The second item would be what we put into the string. Here %02d means we are going to put a 2 digit integer

        gpsNum = gps.satellites.value();
    }

    else //If we do not get the date from the GPS module
    {
        strcpy(GPS_dateString,"DD/MM/YY"); 
        strcpy(gpsDate,"000000");
        // strcpy is a function called string copy, in which we copy the second item in the first item, 
        //which is the place where we store the string
    }
//-------------------------------------------------------------------------------------------------------------------------------//
// Encoding the GPS time String ------------------------------------------------------------------------------------------------//
    if (gps.time.isValid())
    {
        sprintf(GPS_timeString,"%02d:%02d:%02d",gps.time.hour() , gps.time.minute(), gps.time.second());
        sprintf(gpsTime,"%02d%02d%02d",gps.time.hour() , gps.time.minute(), gps.time.second());
    }

    else
    {
        strcpy(GPS_timeString,"Time");
        strcpy(gpsTime,"000000");
    }
//-------------------------------------------------------------------------------------------------------------------------------//
// Encoding the GPS location String --------------------------------------------------------------------------------------------//
    if (gps.location.isValid())
    {
        gpsLat = gps.location.lat();
        gpsLng = gps.location.lng();
        gpsAlt = gps.altitude.meters();
        

        GPSlogoSprite.drawString("GPS",0,0,4);
        GPSlogoSprite.pushSprite (140,0,TFT_GREY);
    }

    else
    {
        gpsLat = -99.999994;
        gpsLng = -444.444444;
        gpsAlt = 99999.9;
    }
    
}
