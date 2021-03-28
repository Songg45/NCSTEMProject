#pragma once
#include <string>
#include "Serial.h"

void ReadAndConvertLocalGPS(char message[750], std::string& GPSCoords, bool& Success, double& GPSNSConverted, double& GPSEWConverted, Serial SerialPort);