// This .cpp file contains the functions for The Main Page of the device

#include <FS.h>
#include <TFT_eSPI.h>         //Include library for SPI TFT display
#include <TFT_eWidget.h>      //Include library for TFT buttons

#include "ButtonWidget.h"
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
//-----------------------------------------------------//
//Buttons---------------------------------------------//
ButtonWidget DHT_Button = ButtonWidget(&tft);
ButtonWidget BMP_Button = ButtonWidget(&tft);
ButtonWidget Dose_Button = ButtonWidget(&tft);
ButtonWidget Prev_Button = ButtonWidget(&tft);
ButtonWidget Next_Button = ButtonWidget(&tft);

#define BUTTON_W 75
#define BUTTON_H 35
#define PageButton_W 110
#define PageButton_H 30

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

//Create an array of button instances to use in for() loops
//This is more useful where large numbers of buttons are employed
ButtonWidget *buttons [] = {&DHT_Button, &BMP_Button, &Dose_Button, &Prev_Button, &Next_Button};;
uint8_t buttonCount = sizeof(buttons) / sizeof(buttons[0]);

uint16_t t_x = 9999, t_y = 9999; //To store the touch coordinates

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

    DoseSprite.createSprite (60,28);  // The Dose rate display
    DoseSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    TempSprite.createSprite (65,28);  // The Temperature display
    TempSprite.setTextColor(TFT_WHITE,TFT_BLACK);

    RHSprite.createSprite (65,28);  // The Humidity display
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
//Here, print the standard display table on the TFT
//The Blue outline making the interface looks better
    tft.fillSmoothRoundRect(0,18,240,108,4,TFT_CYAN,TFT_BLACK);
    tft.fillSmoothRoundRect(4,21,232,100,4,TFT_BLACK,TFT_BLACK);
//------------------------------------------------------------------------------
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0,28);
    tft.print ("  Dose:");
    tft.setCursor(160,28);
    tft.print ("uSv/hr");

    tft.setCursor(10,53);
    tft.print (" Temp.:");
    tft.setCursor(170,53);
    tft.print ((char)247);  // (char)247 is the deg. symbol 
    tft.print("C");

    tft.setCursor(6,78);
    tft.print (" Humid.:");
    tft.setCursor(180,78);
    tft.print ("%");

    tft.setCursor(6,103);
    tft.print (" Press.:");
    tft.setCursor(200,103);
    tft.print ("hPa");

}


void ShowBasicData ()
{
    const int DataAlign_X = 100;
    const int DataGapDistance_Y = 25;

    BatterySprite.drawString("BATTERY: ",0,0,2);
    BatterySprite.pushSprite (150,0,TFT_BLACK);

    DoseSprite.drawString(String(MinuteDoseRate),0,0,4);
    DoseSprite.pushSprite (DataAlign_X - 4,25,TFT_GREY);

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
    GPSdateSprite.drawString(String(GPS_dateString),0,0,2);
    GPSdateSprite.pushSprite (0,300,TFT_GREY);

    GPStimeSprite.drawString(String(GPS_timeString),0,0,2);
    GPStimeSprite.pushSprite (100,300,TFT_GREY);

    //Testing if logo shows up
    // GPSlogoSprite.drawString("GPS",0,0,4);
    // GPSlogoSprite.pushSprite (140,0,TFT_GREY);
}

//Dose Button press and release-------------------------------------------------------------------------------//
void Dose_Button_pressAction ()
{
    if (Dose_Button.justPressed())
    {
        Dose_Button.drawSmoothButton(!Dose_Button.getState(), 3, TFT_BLACK, "Dose");
        Dose_Button.setPressTime(millis());
        Serial.println ("Dose pressed");
        Serial.println (t_x);
        Serial.println (t_y);

    }
}

void Dose_Button_releaseAction ()
{

}
//-----------------------------------------------------------------------------------------------------------//
//DHT Button press and release-------------------------------------------------------------------------------//
void DHT_Button_pressAction ()
{
    if (DHT_Button.justPressed())
    {
        DHT_Button.drawSmoothButton(!DHT_Button.getState(), 3, TFT_BLACK, "DHT");
        DHT_Button.setPressTime(millis());
        Serial.println ("DHT pressed");
        Serial.println (t_x);
        Serial.println (t_y);
    }
}

void DHT_Button_releaseAction ()
{

}
//-----------------------------------------------------------------------------------------------------------//
//BMP Button press and release-------------------------------------------------------------------------------//
void BMP_Button_pressAction ()
{
    if (BMP_Button.justPressed())
    {
        BMP_Button.drawSmoothButton(!BMP_Button.getState(), 3, TFT_BLACK, "BMP");
        BMP_Button.setPressTime(millis());
        Serial.println ("BMP pressed");
        Serial.println (t_x);
        Serial.println (t_y);
    }
}

void BMP_Button_releaseAction ()
{

}
//-----------------------------------------------------------------------------------------------------------//
//Prev Button press and release------------------------------------------------------------------------------//
void Prev_Button_pressAction ()
{
    if (Prev_Button.justPressed())
    {
        Prev_Button.drawSmoothButton(!Prev_Button.getState(), 3, TFT_BLACK, "Prev.");
        Prev_Button.setPressTime(millis());
        Serial.println ("Prev pressed");
        Serial.println (t_x);
        Serial.println (t_y);
    }
}

void Prev_Button_releaseAction ()
{

}
//-----------------------------------------------------------------------------------------------------------//
//Next Button press and release------------------------------------------------------------------------------//
void Next_Button_pressAction ()
{
    if (Next_Button.justPressed())
    {
        Next_Button.drawSmoothButton(!Next_Button.getState(), 3, TFT_BLACK, "Next");
        Next_Button.setPressTime(millis());
        Serial.println ("Next pressed");
        Serial.println (t_x);
        Serial.println (t_y);
    }
}

void Next_Button_releaseAction ()
{

}
//-----------------------------------------------------------------------------------------------------------//

void initButtons ()
{
    uint16_t x = 0;
    uint16_t y = 230;

    Dose_Button.initButtonUL (x,y,BUTTON_W, BUTTON_H,TFT_WHITE,TFT_CYAN,TFT_BLACK,"  Dose", 1);
    Dose_Button.setPressAction(Dose_Button_pressAction);
    //Dose_Button.setReleaseAction(Dose_Button_releaseAction);
    Dose_Button.drawSmoothButton(false, 3, TFT_BLACK);

    x = 80;
    DHT_Button.initButtonUL (x,y,BUTTON_W, BUTTON_H,TFT_WHITE,TFT_CYAN,TFT_BLACK,"  DHT", 1);
    DHT_Button.setPressAction(DHT_Button_pressAction);
    //DHT_Button.setReleaseAction(DHT_Button_releaseAction);
    DHT_Button.drawSmoothButton(false, 3, TFT_BLACK);

    x = 160;
    BMP_Button.initButtonUL (x,y,BUTTON_W, BUTTON_H,TFT_WHITE,TFT_CYAN,TFT_BLACK,"  BMP", 1);
    BMP_Button.setPressAction(BMP_Button_pressAction);
    //BMP_Button.setReleaseAction(BMP_Button_releaseAction);
    BMP_Button.drawSmoothButton(false, 3, TFT_BLACK);

    x = 0;
    y = 270;
    Prev_Button.initButtonUL (x,y,PageButton_W, PageButton_H,TFT_WHITE,TFT_CYAN,TFT_BLACK," Prev.", 1);
    Prev_Button.setPressAction(Prev_Button_pressAction);
    //Prev_Button.setReleaseAction(Prev_Button_releaseAction);
    Prev_Button.drawSmoothButton(false, 3, TFT_BLACK);

    x = 120;
    Prev_Button.initButtonUL (x,y,PageButton_W, PageButton_H,TFT_WHITE,TFT_CYAN,TFT_BLACK," Next", 1);
    Prev_Button.setPressAction(Next_Button_pressAction);
    //Prev_Button.setReleaseAction(Next_Button_releaseAction);
    Prev_Button.drawSmoothButton(false, 3, TFT_BLACK);
}

void Buttons_Loop ()
{
   
        bool pressed = tft.getTouch (&t_x, &t_y);
        

        for (uint8_t b = 0;b < buttonCount; b++)
        {
            //Serial.print (b);
            if (pressed)
            {
                if (buttons[b]->contains(t_x,t_y))
                {
                    buttons[b]->press(true);
                    buttons[b]->pressAction();
                }
            }

            else
            {
                buttons[b]->press(false);
                buttons[b]->releaseAction();
            }
        }
}
/*
void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!LittleFS.begin()) {
    Serial.println("Formating file system");
    LittleFS.format();
    LittleFS.begin();
  }

  // check if calibration file exists and size is correct
  if (LittleFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      LittleFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f;
      f = LittleFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = LittleFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}
*/