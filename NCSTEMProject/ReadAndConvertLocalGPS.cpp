#include "GetGPSCoords.h"
#include "ConvertGPSCoords.h"
#include "Serial.h"

void ReadAndConvertLocalGPS(char message[750], std::string& GPSCoords, bool& Success, double& GPSNSConverted, double& GPSEWConverted, Serial SerialPort)

{
	int TryCounter = 0;

	do
	{

		SerialPort.read(message, sizeof(message));

		SplitGPSMessage(message, GPSCoords);
		ConvertGPSCoords(GPSCoords, Success, GPSNSConverted, GPSEWConverted);

		TryCounter++;

		if (TryCounter == 4)
		{

			printf("Try Counter exceeded tries.\r\n");
			break;

		}

	} while (!Success);

}