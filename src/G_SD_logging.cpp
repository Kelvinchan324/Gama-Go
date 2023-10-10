// This .cpp file contains the functions for SD card logging

#include <SoftwareSerial.h>

#include "0_Config.h"
#include "1_Global.h"

SoftwareSerial SD_Serial (OpenLogTX,OpenLogRX);

void SD_init ()
{
    SD_Serial.begin(9600);
}

void SD_SendData ()
{
    SD_Serial.println(DataString);
}