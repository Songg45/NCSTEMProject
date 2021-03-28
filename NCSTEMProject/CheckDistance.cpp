#include "CheckDistance.h"
void CheckDistance(double AvgGPSCoordSentEW1, double AvgGPSCoordSentEW2, double AvgGPSCoordSentNS1, double AvgGPSCoordSentNS2, double AvgGPSCoordsSentNS, double AvgGPSCoordsSentEW, 
				   double AvgGPSCoordLocalEW1, double AvgGPSCoordLocalEW2, double AvgGPSCoordLocalNS1, double AvgGPSCoordLocalNS2, double AvgGPSCoordsLocalNS, double AvgGPSCoordsLocalEW, 
				   bool& PlayAlert)
{

	double DistanceNSUp = AvgGPSCoordsSentNS + 0.001;
	double DistanceEWLeft = AvgGPSCoordsSentEW + 0.001;
	double DistanceNSDown = AvgGPSCoordsSentNS - 0.001;
	double DistanceEWRight = AvgGPSCoordsSentEW - 0.001;

	AvgGPSCoordsSentEW = (AvgGPSCoordSentEW1 + AvgGPSCoordSentEW2) / 2;
	AvgGPSCoordsSentNS = (AvgGPSCoordSentNS1 + AvgGPSCoordSentNS2) / 2;

	AvgGPSCoordsLocalEW = (AvgGPSCoordLocalEW1 + AvgGPSCoordLocalEW2) / 2;
	AvgGPSCoordsLocalNS = (AvgGPSCoordLocalNS1 + AvgGPSCoordLocalNS2) / 2;

	if (AvgGPSCoordsLocalNS < DistanceNSUp && AvgGPSCoordsLocalNS > DistanceNSDown && AvgGPSCoordsLocalEW < DistanceEWLeft && AvgGPSCoordsLocalEW > DistanceEWRight)
	{

		PlayAlert = true;

	}
	else
	{

		PlayAlert = false;

	}

}
