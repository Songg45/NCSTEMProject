#include "CheckDistance.h"
#include <iostream>
#include <math.h>
#include <algorithm>

#define PI 3.14159265358979323846
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180
using namespace std;

float CalcGPSDistance(float latitud1, float longitud1, float latitud2, float longitud2) 
{
	double haversine;
	double temp;
	double distancia_puntos;

	latitud1 = latitud1 * GRADOS_RADIANES;
	longitud1 = longitud1 * GRADOS_RADIANES;
	latitud2 = latitud2 * GRADOS_RADIANES;
	longitud2 = longitud2 * GRADOS_RADIANES;

	haversine = (pow(sin((1.0 / 2) * (latitud2 - latitud1)), 2)) + ((cos(latitud1)) * (cos(latitud2)) * (pow(sin((1.0 / 2) * (longitud2 - longitud1)), 2)));
	temp = 2 * asin(min(1.0, sqrt(haversine)));
	distancia_puntos = RADIO_TERRESTRE * temp;

	return distancia_puntos;
}

void CheckDistance(double AvgGPSCoordSentEW1, double AvgGPSCoordSentEW2, double AvgGPSCoordSentNS1, double AvgGPSCoordSentNS2, double AvgGPSCoordsSentNS, double AvgGPSCoordsSentEW, 
				   double AvgGPSCoordLocalEW1, double AvgGPSCoordLocalEW2, double AvgGPSCoordLocalNS1, double AvgGPSCoordLocalNS2, double AvgGPSCoordsLocalNS, double AvgGPSCoordsLocalEW, 
				   bool& PlayAlert)
{

	double DistanceBetweenGPSCoords = 0;


	AvgGPSCoordsSentEW = (AvgGPSCoordSentEW1 + AvgGPSCoordSentEW2) / 2;
	AvgGPSCoordsSentNS = (AvgGPSCoordSentNS1 + AvgGPSCoordSentNS2) / 2;

	AvgGPSCoordsLocalEW = (AvgGPSCoordLocalEW1 + AvgGPSCoordLocalEW2) / 2;
	AvgGPSCoordsLocalNS = (AvgGPSCoordLocalNS1 + AvgGPSCoordLocalNS2) / 2;

	DistanceBetweenGPSCoords = CalcGPSDistance(AvgGPSCoordsSentEW, AvgGPSCoordsSentNS, AvgGPSCoordsLocalEW, AvgGPSCoordsLocalNS);

	if (AvgGPSCoordsLocalNS)
	{

		PlayAlert = true;

	}
	else
	{

		PlayAlert = false;

	}

}
