#include "GetGPSCoords.h"
#include <string>

void SplitGPSMessage(char GPSMessage[750], std::string &GPSCoords)
{
	std::string GPSMessageString(GPSMessage);
	std::string GPSMessageSplit = "";
	std::string GPSSplitPrevious = "";
	std::string delimiter = ",";
	std::string GPSNorthSouthPos = "";
	std::string GPSEastWestPos = "";
	std::size_t GPSMessageLineEnd = GPSMessageString.find("\r\n");

	size_t last = 0; 
	size_t next = 0;

	while ((next = GPSMessageString.find(delimiter, last)) < GPSMessageLineEnd)
	{ 

		GPSSplitPrevious = GPSMessageSplit;

		GPSMessageSplit = GPSMessageString.substr(last, next - last);
		last = next + 1;

		if (GPSMessageSplit == "N")
		{
			GPSSplitPrevious = GPSSplitPrevious.insert(0,"1");
			GPSNorthSouthPos = GPSSplitPrevious;
		}
		else if (GPSMessageSplit == "S")
		{
			GPSSplitPrevious = GPSSplitPrevious.insert(0, "0");
			GPSNorthSouthPos = GPSSplitPrevious;
		}
		else if (GPSMessageSplit == "W" || GPSMessageSplit == "E")
		{
			GPSEastWestPos = GPSSplitPrevious;
		}
	
	} 

	GPSCoords = GPSNorthSouthPos + "," + GPSEastWestPos;
	return;
}