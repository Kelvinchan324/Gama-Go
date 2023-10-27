#include <Arduino.h>         //Include library for Arduino framework (used in Platformio)

#include <Adafruit_Sensor.h>  //Include library for DHT22
#include <DHT.h>             //Include library for DHT22
#include <DHT_U.h>           //Include library for DHT22
#include <Adafruit_BMP085.h>  //Include library for BMP180
#include <TFT_eSPI.h>         //Include library for SPI TFT display
#include <TFT_eWidget.h>      //Include library for TFT buttons 
#include <SoftwareSerial.h>   // Include library for creating extra UART pins for communication
#include <TinyGPS++.h>       //Include library for GPS

#include "0_Config.h"
#include "1_Global.h"
#include "2_Colors.h"
#include "A1_DisplayInitPage.h"
#include "A2_DisplayMainPage.h"
#include "A2_DHTgraph.h"
#include "A2_BMPgraph.h"
#include "A2_DoseGraph.h"
#include "B_GPS.h"
#include "C_DHT.h"
#include "D_BMP.h"
#include "E_GM.h"
#include "F_ESP_BLE.h"
#include "G_SD_logging.h"

uint8_t CurrentCycle, prevMin;
float stnT[12],stnRH[12],stnP[12];

void setup()
{
  Serial.begin(9600);
  touch_calibrate();

  BLE_init();
  SD_init();

  DHTinit();
  bmpInit();
  gpsInit();
  GMinit ();
  
  TFT_init();

  drawDHTgraph();
  CreateBasicData ();
  ShowID();
  initButtons();
  

  

  CurrentCycle = 0;
  prevMin = CurrentCycle;

  //GMinit ();

}

void loop()
{

  Serial.println ("Start of loop");
  CurrentCycle = int((millis()%60000)/5000); 
  // This "CurrentCycle" shows the current cycle of the device, There are 12 stages (0-11) in each cycle
  // The Cycle is looped every one minute and hence 5 seconds for one stage
  // This 5 seconds stage is used to display the data on the display page in the old device
  //----------------------------------------------------------------------------------------------------------//
  //Conditions not performed only every 5 seconds
  
  Buttons_Loop();
  Serial.println ("But loop");


  if (CurrentCycle != prevMin) //This if condition is passed every 5 seconds, as CurrentCycle changes every 5 secs 
  {
    GetDoseRate();

    GetDHTevent();
    GetBMPevent();

    getGPS(); //This functions takes around 1 second to run, so put it in once per 5 seconds (Checling GPS)

    Buttons_Loop();
    Serial.println ("But in loop");

    //ShowBasicData();
    //PrintGPSstring();
    //DisplayGPSdata();
  
    //plotDHTgraph();

    // OutputDataString();
    // BLE_SendDataString();
    // SD_SendData();
    //Serial.println(DataString);

    prevMin = CurrentCycle; // This condition will no longer be true after 5 secs and passes the if condition again
  }
  Serial.println ("End of loop");
  
}
