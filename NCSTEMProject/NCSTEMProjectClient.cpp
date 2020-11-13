#include <stdio.h>
#include "tchar.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    //UDP Data
    int addrlen, msglen;
    char message[300];
    int err, opt = 1;
    SOCKET s;
    struct sockaddr_in hum, addr;

    double ReceivedPackets = 1;

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
    hum.sin_port = htons(52428);

    //UDP SOCKET Binding 
    if (bind(s, (sockaddr*)&hum, sizeof(hum)) == SOCKET_ERROR)
    {
        printf("\nUDP socket binding failed ERROR CODE : %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }

    while (true)
    {
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

        printf("Got server broadcast");
        printf("\nport: %hu", ntohs(addr.sin_port));
        printf("\nMessage: %.*s", msglen, message);
        printf("\nReceived Packet #: %f\n\n", ReceivedPackets);
        ReceivedPackets++;
    }

}