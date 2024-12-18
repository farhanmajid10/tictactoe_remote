#include <iostream>

#include<winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT "8080"

int main(){
    WSADATA wsa_data;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(iResult != 0){
        std::cout << "WSAStartUP failed." << std::endl;
        return 1;
    }

    memset(&hints, 0, sizeof(hints));//puts zeros from the starting point up to the number mentioned.
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

   iResult = getaddrinfo(NULL, PORT, &hints, &result);
   if(iResult != 0){
    std::cout << "getaddrinfo failed." << iResult << std::endl;
    WSACleanup();
    return 1;
   }

   listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(listenSocket == INVALID_SOCKET){
        std::cerr << "listenSocket is not working." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    

}