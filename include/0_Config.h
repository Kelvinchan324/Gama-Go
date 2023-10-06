//Define Pin numbers here
//This Header file must only contain #define variables which are Pin configurations 

# ifndef PinConfig_H_
# define PincConfig_H_

//This value stores the Device ID, each school and device will have a different device ID accordingly
#define DeviceID  "00000"

//This part defines the different Pin layouts of the device -----------------------------------------------------//

#define BATTERY_PIN  13;  // Pin for measuring battery voltage
//#define resetOpenLog 14      //This pin (D14) resets OPenlog
#define GPSRX 16             //Setup GPS RX Pin
#define GPSTX 17             //Setup GPS TX Pin
// For BMP180, SDA connects to D21, & SCL connects to D22
#define BUZ 27
#define DHTPIN 26           //Setup digital pin connected to DHT22
#define OpenLogTX 33          //Setup SD card logger TX Pin (Set RX in esp32)
#define OpenLogRX 32          //Setup SD card logger RX Pin (Set TX in esp32)
#define GMpin 35            //Setip GM counter trigger pin
#define DHTTYPE    DHT22    // Setup type of DHT sensor used
//---------------------------------------------------------------------------------------------------------------//
//Battery indicator setup----------------------------------------------------------------------------------------//
const float ADC_Calibration_Constant = 0.00365; //Calibration constant for ADC reading to voltage
const float R1 = 68000.0;
//Other basic information for the device here -------------------------------------------------------------------//
#define ConFactor 0.0057   //This variable defines the CPM to dose rate conversion factor



#endif