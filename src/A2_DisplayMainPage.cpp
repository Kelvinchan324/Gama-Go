// This .cpp file contains the functions for The Main Page of the device

#include <TFT_eSPI.h>         //Include library for SPI TFT display
#include <TFT_eWidget.h>      //Include library for TFT buttons

#include "0_Config.h"       // Include header file for Pin configuration
#include "1_Global.h"            // Include header file for Global variables
#include "2_Colors.h"            // Include header file for Color used in TFT


//Creating TFT sprites for displaying data--------------//
TFT_eSprite Background = TFT_eSprite (&tft);

TFT_eSprite BatterySprite = TFT_eSprite (&tft);
TFT_eSprite DoseSprite = TFT_eSprite (&tft);
TFT_eSprite TempSprite = TFT_eSprite (&tft);
TFT_eSprite RHSprite = TFT_eSprite (&tft);
TFT_eSprite AtmSprite = TFT_eSprite (&tft);
TFT_eSprite GPSdateSprite = TFT_eSprite (&tft);
TFT_eSprite GPStimeSprite = TFT_eSprite (&tft);
TFT_eSprite GPSlogoSprite = TFT_eSprite (&tft); //For print GPS on screen when there is location

//-----------------------------------------------------//
//Creating TFT sprites for plotting graphs------------//

TFT_eSprite RadiationGraphSprite = TFT_eSprite (&tft);
TFT_eSprite DHTGraphSprite = TFT_eSprite (&tft);
TFT_eSprite BMPGraphSprite = TFT_eSprite (&tft);
//----------------------------------------------------//
int DataAlign_X;
int DataGapDistance_Y;

void ShowID ()
{
    tft.setTextSize(2);
    tft.setCursor(0,0);
    tft.print ("ID:" );
    tft.print (DeviceID);
}


void CreateBasicData ()
{

//Here the Sprites that are used were created-------------------------------------------------------------------//
    BatterySprite.createSprite (100,20); // The Battery percentage on right upper corner
    BatterySprite.setTextColor(TFT_WHITE,TFT_BLACK); 
    //Set the text color with function < TFT_espiSprite.setTextColor("font color","background color"); >

    DoseSprite.createSprite (70,28);  // The Dose rate display
    DoseSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    TempSprite.createSprite (70,28);  // The Temperature display
    TempSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    RHSprite.createSprite (70,28);  // The Humidity display
    RHSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    AtmSprite.createSprite (90,21);  //The pressure display
    AtmSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    GPSdateSprite.createSprite (125,28); //The GPS Date display
    GPSdateSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    GPStimeSprite.createSprite (100,28); //The GPS Time display
    GPStimeSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    GPSlogoSprite.createSprite (50,20); //The GPS logo display
    GPSlogoSprite.setTextColor(TFT_WHITE,TFT_BLACK);

//--------------------------------------------------------------------------------------------------------------//
//Here the print the standard display table on the TFT
    //The Blue outline making the interface looks better
    tft.fillSmoothRoundRect(0,18,320,108,4,TFT_BLUE,TFT_BLACK);
    tft.fillSmoothRoundRect(4,21,312,100,4,TFT_BLACK,TFT_BLACK);
//------------------------------------------------------------------------------
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0,28);
    tft.print ("   Dose: ");
    tft.setCursor(235,28);
    tft.print ("uSv/hr");

    tft.setCursor(10,53);
    tft.print ("Temperature: ");
    tft.setCursor(230,53);
    tft.print ((char)247);  // (char)247 is the deg. symbol 
    tft.print("C");

    tft.setCursor(0,78);
    tft.print (" Humidity: ");
    tft.setCursor(230,78);
    tft.print ("%");

    tft.setCursor(0,103);
    tft.print (" Pressure: ");
    tft.setCursor(260,103);
    tft.print ("hPa");


    tft.setCursor(0,300);
    tft.print (String(gps.location.isValid()) );
    tft.setCursor(0,320);
    tft.print (String(gpsLat) );
    tft.setCursor(0,340);
    tft.print (String(gpsLng) );
    tft.setCursor(0,360);
    tft.print (String(gpsAlt) );
    tft.setCursor(0,380);
    tft.print (String(gpsNum) );
    tft.setCursor(0,400);
    tft.print (String(gpsSerial.read()) );
    Serial.println(String(gpsSerial.read()) );

    
    

}


void ShowBasicData ()
{
    const int DataAlign_X = 160;
    const int DataGapDistance_Y = 25;

    BatterySprite.drawString("BATTERY: ",0,0,2);
    BatterySprite.pushSprite (200,0,TFT_BLACK);

    DoseSprite.drawString(String(MinuteDoseRate),0,0,4);
    DoseSprite.pushSprite (DataAlign_X,25,TFT_GREY);

    //TempSprite.fillSprite(TFT_BLACK);
    TempSprite.drawString(String(DHTtemp),0,0,4);
    TempSprite.pushSprite (DataAlign_X,25 + DataGapDistance_Y,TFT_GREY);

    //RHSprite.fillSprite(TFT_BLACK);
    RHSprite.drawString(String(DHThum),0,0,4);
    RHSprite.pushSprite (DataAlign_X,(25 + 2* DataGapDistance_Y),TFT_GREY);

    AtmSprite.drawString(String(BMPpressure),0,0,4);
    AtmSprite.pushSprite (DataAlign_X,(25 + 3* DataGapDistance_Y),TFT_GREY);

}

void DisplayGPSdata () // Here we print the Dates on the TFT display
{
    GPSdateSprite.fillSprite(TFT_BLACK);
    GPSdateSprite.drawString(String(GPS_dateString),0,0,4);
    GPSdateSprite.pushSprite (0,450,TFT_GREY);

    GPStimeSprite.drawString(String(GPS_timeString),0,0,4);
    GPStimeSprite.pushSprite (130,450,TFT_GREY);

    //Testing if logo shows up
    // GPSlogoSprite.drawString("GPS",0,0,4);
    // GPSlogoSprite.pushSprite (140,0,TFT_GREY);
}