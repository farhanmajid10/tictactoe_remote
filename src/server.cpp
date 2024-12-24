
#include<server.h>
#define PORT "8080"

server::server(){

    iResult = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(iResult != 0){
        std::cout << "WSAStartUP failed." << std::endl;
        return;
    }

    memset(&hints, 0, sizeof(hints));//puts zeros from the starting point up to the number mentioned.
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

   iResult = getaddrinfo(NULL, PORT, &hints, &result);//dynamic allocation of the result happens here.
   if(iResult != 0){
    std::cout << "getaddrinfo failed." << iResult << std::endl;
    WSACleanup();
    return;
   }

   listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(listenSocket == INVALID_SOCKET){
        std::cerr << "listenSocket is not working." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return ;
    }

    iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);
    if(iResult != 0){
        std::cout << "binding failed." << iResult << std::endl;
        closesocket(listenSocket);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);//it gets freed here.

    iResult = listen(listenSocket, SOMAXCONN);
    if(iResult != 0){
        std::cout << "listen did not work." << iResult << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    clientSocket = accept(listenSocket, NULL, NULL);
    if(clientSocket == INVALID_SOCKET){
        std::cout << "client socket was not accepted correctly." << clientSocket << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
}

void server::run(){
    //client connected.

    const char* sendbuf = "welcome to server";//setting string to char* needs a const char.
    char receivebuf[500];
    int recievelen = 500;

    iResult = send(clientSocket, sendbuf,(int) strlen(sendbuf), 0);
    if(iResult == SOCKET_ERROR){
        std::cerr << "cound't send." << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    std::cout << "message sent." << std::endl;

    iResult = recv(clientSocket, receivebuf, recievelen - 1, 0);
    if(iResult > 0){
        receivebuf[iResult] = '\0';
        std::cout << "bytes received: " << iResult << " Message: " << receivebuf <<std::endl;
    }else if(iResult == 0){
        std::cout << "connection closing." << std::endl;
    }else{
        std::cerr << "rcv failed." << WSAGetLastError() << std::endl;
    }

    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    return;
}