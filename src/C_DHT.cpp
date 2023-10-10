// This .cpp file contains the functions for DHT function
  
#include <Adafruit_Sensor.h>  //Include library for DHT22
#include <DHT.h>
#include <DHT_U.h>           //Include library for DHT22

#include "0_Config.h"
#include "1_Global.h"

DHT_Unified dht (DHTPIN,DHTTYPE);
sensors_event_t event; // Get temperature event 

float DHThum;
float DHTtemp;

void DHTinit() 
{
    dht.begin();
}

void GetDHTevent()
{

  dht.humidity().getEvent(&event);
  DHThum = event.relative_humidity;

  dht.temperature().getEvent(&event);
  DHTtemp = event.relative_humidity;



  stnRH[CurrentCycle] = isnan(DHThum) ? -99.99 : DHThum;
  stnT[CurrentCycle] = isnan(DHTtemp) ? -99.99 : DHTtemp;
  /***************   Arguement of "stnT[CurrentCycle] = isnan(DHTtemp) ? -99.99 : DHTtemp;"  *******************************
      stnRH[CurrentCycle]: This refers to an element in the stnRH array at index CurrentCycle. 
        It is assigning a value to this particular element.

      isnan(_h): isnan() is a function that checks whether a given value _h is NaN (Not-a-Number) or not. 
        NaN is a special value used to represent the result of an invalid or undefined

      ? -99.99 : _h: This is a conditional or ternary operator. If the condition isnan(_h) is true, 
        the value -99.99 is assigned to stnRH[CurrentCycle]. If the condition is false, _h is assigned to stnRH[CurrentCycle].
  ********************************************************************************************************************/

}

