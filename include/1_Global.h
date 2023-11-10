//This header files declares all the global variables that will be used in the whole program

#ifndef GLOBAL_H
#define GLOBAL_H
#include <Arduino.h>

//Main Global Variables
extern uint8_t CurrentCycle, prevMin;
extern float stnT[12],stnRH[12],stnP[12];


// Global Variables related to TFT displays (mainly used in part A)----------------------------------------------------//

#include <TFT_eSPI.h>
//**********************************A1_DisplayInitPage***************************************************************//
extern TFT_eSPI tft;
extern TFT_eSprite HKOsprite;
extern TFT_eSprite background;

//*******************************************************************************************************************//
//**********************************A2_DisplayMainPage***************************************************************//

extern TFT_eSprite BatterySprite;
extern TFT_eSprite DoseSprite;
extern TFT_eSprite TempSprite;
extern TFT_eSprite RHSprite;
extern TFT_eSprite AtmSprite;
extern TFT_eSprite GPSdateSprite;
extern TFT_eSprite GPStimeSprite;
extern TFT_eSprite GPSlogoSprite;

extern TFT_eSprite RadiationGraphSprite;
extern TFT_eSprite DHTGraphSprite;
extern TFT_eSprite BMPGraphSprite;

extern bool DosePress;
extern bool DHTPress;
extern bool BMPPress;
// extern ButtonWidget DHT_Button;
// extern ButtonWidget BMP_Button;
// extern ButtonWidget Dose_Button;
// extern ButtonWidget Prev_Button;
// extern ButtonWidget Next_Button;

//--------------------------------------------------------------------------------------------------------------------//
//*****************************************A2_DHTgraph***************************************************************//
extern int originX;
extern int originY;
// Global Variables related to GPS module (used in part B)-----------------------------------------------------------//
#include <SoftwareSerial.h>
#include <TinyGPS++.h> 
extern SoftwareSerial gpsSerial;
extern TinyGPSPlus gps;     


extern double gpsLat, gpsLng, gpsAlt, gpsNum ;
extern char gpsTime[12], gpsDate[12];
extern  char GPS_dateString [10];
extern  char GPS_timeString [10];
//-------------------------------------------------------------------------------------------------------------------//
// Global Variables related to DHT module (used in part C)-----------------------------------------------------------//
#include <DHT.h>
#include <DHT_U.h>

extern DHT_Unified dht;
extern sensors_event_t event;
extern float DHThum;
extern float DHTtemp;
//-------------------------------------------------------------------------------------------------------------------//
// Global Variables related to BMP module (used in part D)-----------------------------------------------------------//
#include <Adafruit_BMP085.h> 

extern Adafruit_BMP085 bmp;
extern float BMPpressure;
//-------------------------------------------------------------------------------------------------------------------//
// Global Variables related to GM tube (used in part E)--------------------------------------------------------------//
extern float MinuteDoseRate;
extern int TotalCounts;
//-------------------------------------------------------------------------------------------------------------------//
// Global Variables related to BLE, string creatiion (used in part F)--------------------------------------------------------------//
extern char DataString [94];

#endif

