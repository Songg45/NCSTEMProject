#include "ConvertGPSCoords.h"
#include <string>
#include <exception>
#include <iostream>

void ConvertGPSCoords(std::string &GPSCoords, bool &Success, double &GPSNSConverted, double &GPSEWConverted)
{
	std::size_t GPSCoordsSplit = GPSCoords.find(",", 0);
	std::string GPSNorthSouth = GPSCoords.substr(0, GPSCoordsSplit);
	std::string GPSEastWest = GPSCoords.substr(GPSCoordsSplit + 1);

	double GPSNSDegrees = 0;
	double GPSNSSeconds = 0;
	double GPSEWDegrees = 0;
	double GPSEWSeconds = 0;

	bool IsGPSNorth = false;
	bool IsGPSWest = false;


	try
	{
	
		GPSNSDegrees = stod(GPSNorthSouth.substr(1, 2));
		GPSNSSeconds = stod(GPSNorthSouth.substr(3));

		GPSEWDegrees = stod(GPSEastWest.substr(1, 2));
		GPSEWSeconds = stod(GPSEastWest.substr(3));

		GPSNSConverted = (GPSNSSeconds / 60) + GPSNSDegrees;
		GPSEWConverted = (GPSEWSeconds / 60) + GPSEWDegrees;

		if (GPSEastWest.substr(0, 1) == "0")
			GPSCoords = std::to_string(GPSNSConverted) + ",-" + std::to_string(GPSEWConverted);

		else
			GPSCoords = std::to_string(GPSNSConverted) + "," + std::to_string(GPSEWConverted);

		Success = true;

		return;

	}

	catch (std::exception exception)
	{

		Success = false;
		return;

	}


}