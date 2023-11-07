//Define Pin numbers here
//This Header file must only contain #define variables which are Pin configurations 

# ifndef Config_H_
# define Config_H_

//This value stores the Device ID, each school and device will have a different device ID accordingly
#define DeviceID  "00000"

#define BLE_DeviceName "GammaGo_00000" //The Bluetooth name of the device
#define SERVICE_UUID "0000ffe0-0000-1000-8000-00805f9b34fb" //This is the UUID for the Bluetooth connection 
#define CHARACTERISTIC_UUID "0000ffe1-0000-1000-8000-00805f9b34fb" //This is the UUID for characteristic
//Please do not change the UUID, as it will affect the connection for the BLE and the webpage
//I found this UUID on the Gamma-Go webpage code


//You can generate the UUID here: https://www.uuidgenerator.net/

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
const float ADC_CALIBRATION_CONSTANT = 0.00365; //Calibration constant for ADC reading to voltage
const float R1 = 68000.0;
const float R2 = 100000.0;

const float MIN_BATTERY_VOLTAGE = 6.0;
const float MAX_BATTERY_VOLTAGE = 8.4;
//Other basic information for the device here -------------------------------------------------------------------//
#define ConFactor 0.0057   //This variable defines the CPM to dose rate conversion factor

# endif