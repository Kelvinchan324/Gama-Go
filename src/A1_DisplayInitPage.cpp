// This .cpp file contains the functions for The initial Page of the device

#include <TFT_eSPI.h>         //Include library for SPI TFT display
#include <TFT_eWidget.h>      //Include library for TFT buttons

#include "0_Config.h"         // Include header file for Pin configuration
#include "1_Global.h"              // Include header file for Global variables
#include "2_Colors.h"              // Include header file for Color used in TFT
#include "A1_DisplayInitPage.h"  // Include the header file for variables define and function declaration
#include "HKOlogo.h"             // Include the .c file for HKO logo pixels
#include "Free_Fonts.h"

TFT_eSPI tft = TFT_eSPI(); //Invoke custom library

//TFT_eSprite HKOsprite = TFT_eSprite (&tft);

int BuzToneArray [] = {1,3,2,4,0,4,2,3,1,0}; //This array stores the different sounds when init. the device
int LoadBarDelayTime = (10/2)*100; //How long each loading bar element is divided (Init page loading for 10sec)

void  TFT_init ()
{ 
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(TFT_SKYBLUE);

  // Displaying HKO logo on the TFT display with sprites
  tft.setSwapBytes (true); // This line of code makes the images normal
  //HKOsprite.createSprite(250,202);  // Creating a Sprite for the HKO logo

  // HKOsprite.setSwapBytes (true);
  // HKOsprite.pushImage(0,0,250,202,HKOlogo); // Push the HKO logo image into the Sprite
  // HKOsprite.pushSprite (0,10,TFT_BLACK); // Push the HKO logo Sprite to the background Sprite
  
   //------------------------------------------------------
  
  tft.setCursor(8,280);
  tft.setTextColor (TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextFont(GLCD);
  tft.print("Device Initializing");

  //Change back to original size for device
  tft.setTextSize(1);
  tft.setTextColor (TFT_WHITE);


  // Plotting the Loading Bar ----------------------------------------------------------------------------//
  int BuzArrayLength = sizeof(BuzToneArray) / sizeof(BuzToneArray[0]);
  for (int i = 0; i < (BuzArrayLength+10); i++)
  {
    if(i<10) //In this if condition the device init. with a rising tone then a falling tone
    {
      tone (BUZ,(BuzToneArray[i]*1000));
    }
    tft.fillSmoothRoundRect ((1 + i*LoadBarX),LoadBarY,LoadBarW,LoadBarH,LoadBarR,WHITE,BLACK);
    delay(LoadBarDelayTime); //Start 0.5s
  }
  //------------------------------------------------------------------------------------------------------//
  //HKOsprite.deleteSprite();

  tft.fillScreen (BLACK);

}
