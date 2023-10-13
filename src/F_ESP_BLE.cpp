// This .cpp file contains the functions for BLE communication and creating the output string
#include<Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "0_Config.h"
#include "1_Global.h"

// BLECharacteristic GammaGoDataCharacteristics ("b336141f-4ba0-4d8f-82ec-769e4142634e",BLECharacteristic::PROPERTY_NOTIFY);
// BLEDescriptor GammaGoDataDescriptor(BLEUUID((uint16_t)0x2902));
//----------------------------------------------------------------------------------------------------------------//

BLEServer* pServer = NULL;
BLECharacteristic*pCharacteristic = NULL;

bool DeviceConnected = false;
bool OldDeviceConnected = false;

//Valuables related to creating the data string------------------------------------------------------------------//
char DataString [94]; //Set an array of char (String) for the final output string
char FormatString [11]; //Create a string (array of char) which helps formatting the Data String, 
//It is used for storing the adjusted data strings and then input to the main DataString
//We set the array with 10 spaces as the adjusted lat has 9 char and lng has 10 char

long int Adjusted_LAT;
long int Adjusted_LNG;
long int Adjusted_MinuteDose;
int Adjusted_Temp;
int Adjusted_RH;
int Adjusted_Pressure;
long int Adjusted_ALT;

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks : public BLEServerCallbacks{
    void onConnect (BLEServer* pServer)
    {
        DeviceConnected = true;
    };

    void onDisconnect (BLEServer* pServer)
    {
        DeviceConnected = false;
    }

};

void BLE_init ()
{   
    //Set up BLE DEvice ---------------------------------------------------------------------//
    BLEDevice::init(BLE_DeviceName); //Create the BLE Device
    //Set up BLE Server --------------------------------------------------------------------//
    pServer = BLEDevice::createServer(); //Set the BLE device as server

    pServer->setCallbacks(new MyServerCallbacks()); //Assign a callback function
    //Set up BLE Service ------------------------------------------------------------------//
    BLEService * pService = pServer->createService(SERVICE_UUID);
    //Set up BLE Characteristic-----------------------------------------------------------//
    pCharacteristic = pService -> createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ   |
        BLECharacteristic::PROPERTY_WRITE  |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_INDICATE
    );
    //Set up BLE Descriptor ------------------------------------------------------------------//
    pCharacteristic ->addDescriptor (new BLE2902());

    //Start the service---- ------------------------------------------------------------------//
    pService -> start();

    //Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising -> addServiceUUID(SERVICE_UUID);
    pAdvertising -> setScanResponse(false);
    pAdvertising -> setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    //Serial.println("Waiting a client connection to notify...");
}

//----------------------------------------------------------------------------------------------
//default string format:%00000&015743,17062023&+25109090,+121806312&0019,0001844,+2970,0740,10077&000801,0,1,00,00%89%
//----------------------------------------------------------------------------------------------
void OutputDataString ()
{
    strcpy(DataString,"%");
    strcat(DataString,DeviceID);
    strcat(DataString,"&");
    // The first three lines of code inputs the Device ID in the Data string with a start of %00000&

    strcat(DataString,gpsTime);
    strcat(DataString,",");
    //The next two lines of code inputs the Time we get from the GPS into the Data String in a form of 235959,

    strcat(DataString,gpsDate);
    strcat(DataString,"&");
    //Here, we input the Date from the GPS in the Data String as well in the form of 02022020& (ddmmyyyy&)

    //GPS lat lng adjustments------------------------------------------------------------------------------------------//
    Adjusted_LAT = long(gpsLat * 1000000);
    sprintf(FormatString,"%+09ld",Adjusted_LAT);
    strcat(DataString,FormatString);
    strcat(DataString,",");
    // These four lines of code adjusts the latitude and inputs it in the storge we created (FormatString)
    // Then it inputs the adjusted latitude into the data string in form of 22302250,

    Adjusted_LNG = long(gpsLng * 1000000);
    sprintf(FormatString,"%+010ld",Adjusted_LNG);
    strcat(DataString,FormatString);
    strcat(DataString,"&");
    // These four lines of code adjusts the longitude and inputs it in the storge we created (FormatString)
    // Then it inputs the adjusted longitude into the data string in form of 114174355&
    //-----------------------------------------------------------------------------------------------------------------//

    //Dose adjustments------------------------------------------------------------------------------------------------//
    sprintf(FormatString,"%04d",TotalCounts);
    strcat(DataString,FormatString);
    strcat(DataString,",");
    // These three lines of code inputs the Total counts from the GM tube into the data string with form 0054,

    Adjusted_MinuteDose = MinuteDoseRate*10000;
    sprintf(FormatString,"%07ld",Adjusted_MinuteDose);
    strcat(DataString,FormatString);
    strcat(DataString,",");
    //First line of code adjusts the minute dose rate value
    //Then the adjusted value is input into the data in the form of 000002345,
    //----------------------------------------------------------------------------------------------------------------//

    //DHT values adjustments------------------------------------------------------------------------------------------//
    Adjusted_Temp = int(DHTtemp * 100);
    sprintf (FormatString,"%+05d",Adjusted_Temp);
    strcat(DataString,FormatString);
    strcat(DataString,",");
    //First line of code adjusts the temperature value from the DHT readings
    //Then the adjusted value is input into the data in the form of +2555,

    Adjusted_RH = int(DHThum * 10);
    sprintf (FormatString,"%04d",Adjusted_RH);
    strcat(DataString,FormatString);
    strcat(DataString,",");
    //First line of code adjusts the humidity value from the DHT readings
    //Then the adjusted value is input into the data in the form of 0678,
    //-----------------------------------------------------------------------------------------------------------------//

    //BMP values adjustments-------------------------------------------------------------------------------------------//
    Adjusted_Pressure = int(BMPpressure * 10);
    sprintf (FormatString,"%05d",Adjusted_Pressure);
    strcat(DataString,FormatString);
    strcat(DataString,"&");
    //First line of code adjusts the pressure value from the BMP readings
    //Then the adjusted value is input into the data in the form of 10011&
    //----------------------------------------------------------------------------------------------------------------//

    Adjusted_ALT = long(gpsAlt * 10);
    sprintf (FormatString,"%06ld",Adjusted_ALT);
    strcat(DataString,FormatString);
    strcat(DataString,",0,1,00,00%89%");
    
    //First line of code adjusts the altitude value from the GPS module
    //Then the adjusted value is input into the data in the form of 100110,0,1,00,00%89%
    //where 00%91% determines the end of the string (also the check sum of the string)

}

void BLE_SendDataString()
{
    if (DeviceConnected) {
        pCharacteristic->setValue(DataString);
        pCharacteristic->notify();
        delay(3); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!DeviceConnected && OldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        //Serial.println("start advertising");
        OldDeviceConnected = DeviceConnected;
    }
    // connecting
    if (DeviceConnected && !OldDeviceConnected) {
        // do stuff here on connecting
        OldDeviceConnected = DeviceConnected;
}
}