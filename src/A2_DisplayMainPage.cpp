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
//-----------------------------------------------------//

//Dimension related to buttons on touchscreen main page----------------------------------------------------------//
// Upper buttons (DHT,BMP,Dose graqh changing)
const int buttonWidth = 100;
const int buttonHeight = 60;
const int upperButtonY = 300;
const int buttonMargin = 10;

// Lower buttons (Previous Page and Next Page)
const int lowerButtonWidth = 140;
const int lowerButtonHeight = 60;
const int lowerButtonY = 380;

// Button colors
const uint16_t buttonColor = TFT_CYAN;
const uint16_t buttonPressedColor = TFT_BLACK;
//-------------------------------------------------------------------------------------------------------------------//

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
//Here, print the standard display table on the TFT
//The Blue outline making the interface looks better
    tft.fillSmoothRoundRect(0,18,320,108,4,TFT_CYAN,TFT_BLACK);
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

//Functions handling Touchscreenn Buttons --------------------------------------------------------//
void drawButton (int x, int y, int width, int height, const char* label, bool pressed)
{
    tft.fillRoundRect(x,y,width,height,10,pressed ? buttonPressedColor : buttonColor);
    tft.drawRoundRect(x,y,width,height,10,TFT_BLACK);
    tft.setTextColor(TFT_BLACK,pressed ? buttonColor : buttonPressedColor);
    tft.setTextSize(2);
    tft.setTextDatum(ML_DATUM); //align to middle right
    tft.drawString(label, x + width/2, y + height/2 );
}

void handleButtonPress (int buttonIndex)
{
    switch (buttonIndex){
        case 1:
            // Handle DHT button press
            // Perform task associated with DHT button
            break;
        case 2:
            // Handle BMP button press
            // Perform task associated with BMP button
            break;
        case 3:
            // Handle Dose button press
            // Perform task associated with Dose button
            break;
        case 4:
            // Handle Previous Page button press
            // Perform task associated with Previous Page button
            break;
        case 5:
            // Handle Next Page button press
            // Perform task associated with Next Page button
            break;
        default:
        break;
  }
}

void Buttons_init ()
{
    //Draw upper buttons
    int buttonX = (tft.width()- 3*buttonWidth - 2*buttonMargin)/2;
    drawButton (buttonX, upperButtonY,buttonWidth,buttonHeight,"DHT",false);
    buttonX += buttonWidth + buttonMargin;
    drawButton (buttonX, upperButtonY,buttonWidth,buttonHeight,"BMP",false);
    buttonX += buttonWidth + buttonMargin;
    drawButton (buttonX, upperButtonY,buttonWidth,buttonHeight,"Dose ",false);
    //Draw lower buttons
    int lowerButtonX = ((tft.width()- 2 * lowerButtonWidth)/2) +2;
    drawButton(lowerButtonX,lowerButtonY,lowerButtonWidth,lowerButtonHeight,"Prev",false);
    lowerButtonX += lowerButtonWidth + buttonMargin;
    drawButton(lowerButtonX, lowerButtonY, lowerButtonWidth, lowerButtonHeight, "Next", false);
}

void ButtonTouchEvent ()
{
    // Check for touch events
    uint16_t t_x, t_y;
    if (tft.getTouch(&t_x, &t_y))
    {
        Serial.println("touch X: "); 
        Serial.println(String(t_x));
        Serial.println("touch Y: ");
        Serial.println(String(t_y));

        // Check if upper buttons were pressed
        int buttonX = (tft.width() - 3 * buttonWidth - 2 * buttonMargin) / 2;
        bool upperButtonPressed = false;
        int pressedButtonIndex = 0;
        if (t_y > upperButtonY && t_y < upperButtonY + buttonHeight) {
        for (int i = 1; i <= 3; i++) {
            if (t_x > buttonX && t_x < buttonX + buttonWidth) {
            upperButtonPressed = true;
            pressedButtonIndex = i;
            break;
            }
            buttonX += buttonWidth + buttonMargin;
        }
        }

        // Check if lower buttons were pressed
        int lowerButtonX = (tft.width() - 2 * lowerButtonWidth) / 2;
        bool lowerButtonPressed = false;
        int lowerPressedButtonIndex = 0;
        if (t_y > lowerButtonY && t_y < lowerButtonY + lowerButtonHeight) {
        for (int i = 4; i <= 5; i++) {
            if (t_x > lowerButtonX && t_x < lowerButtonX + lowerButtonWidth) {
            lowerButtonPressed = true;
            lowerPressedButtonIndex = i;
            break;
            }
            lowerButtonX += lowerButtonWidth;
        }
        }

        // Handle button press
        if (upperButtonPressed) {
        // Reset button colors
        drawButton((tft.width() - 3 * buttonWidth - 2 * buttonMargin) / 2, upperButtonY, buttonWidth, buttonHeight, "DHT", false);
        drawButton((tft.width() - 3 * buttonWidth - 2 * buttonMargin) / 2 + buttonWidth + buttonMargin, upperButtonY, buttonWidth, buttonHeight, "BMP", false);
        drawButton((tft.width() - 3 * buttonWidth - 2 * buttonMargin) / 2 + 2 * (buttonWidth + buttonMargin), upperButtonY, buttonWidth, buttonHeight, "Dose", false);
        
        // Highlight pressed button
        drawButton((tft.width() - 3 * buttonWidth - 2 * buttonMargin) / 2 + (pressedButtonIndex - 1) * (buttonWidth + buttonMargin), upperButtonY, buttonWidth, buttonHeight, pressedButtonIndex == 1 ? "DHT" : (pressedButtonIndex == 2 ? "BMP" : "Dose"), true);

        // Perform task associated with the pressed button
        handleButtonPress(pressedButtonIndex);
        }
        else if (lowerButtonPressed) {
        // Highlight pressed button
        drawButton((tft.width() - 2 * lowerButtonWidth) / 2 + (lowerPressedButtonIndex - 4) * lowerButtonWidth, lowerButtonY, lowerButtonWidth, lowerButtonHeight, lowerPressedButtonIndex == 4 ? "Previous" : "Next", true);

        // Perform task associated with the pressed button
        handleButtonPress(lowerPressedButtonIndex);

        // Reset button color after 1 second delay
        delay(1000);
        drawButton((tft.width() - 2 * lowerButtonWidth) / 2 + (lowerPressedButtonIndex - 4) * lowerButtonWidth, lowerButtonY, lowerButtonWidth, lowerButtonHeight, lowerPressedButtonIndex == 4 ? "Previous" : "Next", false);
        }
  }
}
