#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#define PORT "8080"

int main(){
    WSADATA wsa_data;
    SOCKET clientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(iResult != 0){
        std::cout << "WSAStartUp failed." << std::endl;
        return 1;
    }

    memset(&hints, 0,sizeof(hints));
    //hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(NULL, PORT,&hints, &result);
    if(iResult != 0){
        std::cout << "Getaddrinfo failed." << std::endl;
        //freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(clientSocket == INVALID_SOCKET){
        std::cout << "socket init didn't work." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    } 

    iResult = connect(clientSocket, result->ai_addr, result->ai_addrlen);
    if(iResult != 0){
        std::cout << "connection was not established." << std::endl;
        freeaddrinfo(result);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "connected" << std::endl;

    const char* sendbuf = "Connected to server";
    char receivebuf[500];
    int rbuflength = 500;

    iResult = send(clientSocket, sendbuf, (int)strlen(sendbuf),0);
    if(iResult == SOCKET_ERROR){
        std::cout << "error sending back to server." << iResult << std::endl;
        freeaddrinfo(result);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "sent from cleint to server" << std::endl;

    iResult = recv(clientSocket, receivebuf, rbuflength, 0);
    if(iResult > 0){
        receivebuf[iResult] = '\0';
        std::cout << "message: " << receivebuf << std::endl;
    }else if(iResult == 0){
        std::cout << "connection closed." << std::endl;
    }else{
        std::cerr << WSAGetLastError() << std::endl;
        return 1;
    }


    freeaddrinfo(result);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
