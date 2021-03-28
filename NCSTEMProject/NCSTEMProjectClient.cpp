#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>
#include <Mmsystem.h>
#include <mciapi.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

#include "GetGPSCoords.h"
#include "ConvertGPSCoords.h"
#include "Serial.h"
#include "tchar.h"
#include "CheckDistance.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //UDP Data
    int addrlen, msglen;
    char message[750];
    int err, opt = 1;
    SOCKET s;
    struct sockaddr_in hum, addr;

    std::string GPSCoords;
    bool Success = false;

    double GPSNSConverted = 0;
    double GPSEWConverted = 0;

    double AvgGPSCoordSentNS1 = 0;
    double AvgGPSCoordSentNS2 = 0;
    double AvgGPSCoordSentNS3 = 0;
    double AvgGPSCoordSentEW1 = 0;
    double AvgGPSCoordSentEW2 = 0;
    double AvgGPSCoordSentEW3 = 0;

    double AvgGPSCoordsSentNS = 0;
    double AvgGPSCoordsSentEW = 0;

    double AvgGPSCoordLocalNS1 = 0;
    double AvgGPSCoordLocalNS2 = 0;
    double AvgGPSCoordLocalEW1 = 0;
    double AvgGPSCoordLocalEW2 = 0;

    double AvgGPSCoordsLocalNS = 0;
    double AvgGPSCoordsLocalEW = 0;

    double FirstDistance = 0;
    double SecondDistance = 0;

    std::string AvgGPSCoordsSent;
    std::string AvgGPSCoordsLocal;

    int GPSCoordCounter = 1;
    int TryCounter = 0;
    int DistanceCounter = 1;
    bool PlayAlert = false;

    //Initializing winsock
    WSADATA wsa;
    err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err != 0)
    {
        printf("\nFailed Initializing Winsock EROR CODE : %d\n", err);
        return 1;
    }

    //UDP Socket creation
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
    {
        printf("\nUDP socket creation failed ERROR CODE : %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //UDP Broadcast permissions
    if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt)) == SOCKET_ERROR)
    {
        printf("\nERROR in broadcasting ERROR CODE : %d \n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //UDP socket definition
    memset(&hum, 0, sizeof(addr));
    hum.sin_family = AF_INET;
    hum.sin_addr.s_addr = INADDR_ANY;
    hum.sin_port = htons(55000);

    //UDP SOCKET Binding 
    if (bind(s, (sockaddr*)&hum, sizeof(hum)) == SOCKET_ERROR)
    {
        printf("\nUDP socket binding failed ERROR CODE : %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //Initialize Serial Port
    tstring COMPort(TEXT("COM3"));
    Serial SerialPort(COMPort, 9600);

    while (true)
    {

        GPSCoords = "";
        GPSNSConverted = 0;
        GPSEWConverted = 0;
        Success = false;

        //UDP Receiving broadcasted data
        addrlen = sizeof(addr);
        msglen = recvfrom(s, message, sizeof(message), 0, (struct sockaddr*)&addr, &addrlen);
        if (msglen == SOCKET_ERROR)
        {
            printf("\nUDP Broadcast not received ERROR CODE : %d\n", WSAGetLastError());
            closesocket(s);
            WSACleanup();                           
            return 1;
        }

        SplitGPSMessage(message, GPSCoords);
        ConvertGPSCoords(GPSCoords, Success, GPSNSConverted, GPSEWConverted);

        if (Success)
        {

            Success = false;

            switch (GPSCoordCounter)
            {

            case 1:
                AvgGPSCoordSentEW1 = GPSEWConverted;
                AvgGPSCoordSentNS1 = GPSNSConverted;

                TryCounter = 0;

                do
                {

                    SerialPort.read(message, sizeof(message));
                    SplitGPSMessage(message, GPSCoords);
                    ConvertGPSCoords(GPSCoords, Success, GPSNSConverted, GPSEWConverted);

                    TryCounter++;

                    if (TryCounter == 4)
                    {

                        break;

                    }

                } while (!Success);

                if (Success)
                {

                    AvgGPSCoordLocalEW1 = GPSEWConverted;
                    AvgGPSCoordLocalNS1 = GPSNSConverted;
                    GPSCoordCounter++;

                }

                break;

            case 2:
                AvgGPSCoordSentEW2 = GPSEWConverted;
                AvgGPSCoordSentNS2 = GPSNSConverted;

                TryCounter = 0;

                do
                {

                    SerialPort.read(message, sizeof(message));
                    SplitGPSMessage(message, GPSCoords);
                    ConvertGPSCoords(GPSCoords, Success, GPSNSConverted, GPSEWConverted);

                    TryCounter++;

                    if (TryCounter == 4)
                    {

                        break;

                    }

                } while (!Success);

                if (Success)
                {

                    AvgGPSCoordLocalEW2 = GPSEWConverted;
                    AvgGPSCoordLocalNS2 = GPSNSConverted;
                    GPSCoordCounter = 1;

                    CheckDistance(AvgGPSCoordSentEW1, AvgGPSCoordSentEW2, AvgGPSCoordSentNS1, AvgGPSCoordSentNS2, AvgGPSCoordsSentNS, AvgGPSCoordsSentEW, 
                        AvgGPSCoordLocalEW1, AvgGPSCoordLocalEW2, AvgGPSCoordLocalNS1, AvgGPSCoordLocalNS2,
                        AvgGPSCoordsLocalNS, AvgGPSCoordsLocalEW, 
                        PlayAlert, FirstDistance, SecondDistance, DistanceCounter);

                    if (PlayAlert)
                    {

                        printf("Warning! Vehicle detected\r\n");
                        Beep(900, 800);

                    }
 
                }

                break;

            }


        }

    }

}