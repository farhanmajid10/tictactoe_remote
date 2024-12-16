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

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    

}