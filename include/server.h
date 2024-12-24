#ifndef SERVER_H
#define SERVER_H

#include <iostream>

#include<winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class server{
private:
    WSADATA wsa_data;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;
    int iResult;
public:
    server();
    void run();
};


#endif