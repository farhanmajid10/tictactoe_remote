#include <client.h>
#include<board.h>
#include<string>
#include<memory>
#define PORT "8080"

client::client(){
    iResult = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(iResult != 0){
        std::cout << "WSAStartUp failed." << std::endl;
        return;
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
        return;
    }

    clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(clientSocket == INVALID_SOCKET){
        std::cout << "socket init didn't work." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    } 

    iResult = connect(clientSocket, result->ai_addr, result->ai_addrlen);
    if(iResult != 0){
        std::cout << "connection was not established." << std::endl;
        freeaddrinfo(result);
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    std::cout << "connected" << std::endl;
}

void client::run(){
    const char* sendbuf = "Connected to server";
    char receivebuf[500];
    int rbuflength = 500;

    Board board;
    int player2_input;

    while(board.check() == 0 && board.is_draw() == 0){
        std::cout << "Wait for other player." << std::endl;
        iResult = recv(clientSocket, receivebuf, 10, 0);
        if(iResult > 0){
            receivebuf[iResult] = '\0';
            std::shared_ptr<char[]> temp(new char[9],[](char* ptr){delete[] ptr;});
            memcpy(temp.get(), receivebuf, 9);
            board.set_game(temp);
            board.set_turns(receivebuf[9] - '0');
            board.printboard();
            std::cout << std::endl;
            //std::cout << "message: " << receivebuf << std::endl;
        }else if(iResult == 0){
            std::cout << "connection closed." << std::endl;
        }else{
            std::cerr << WSAGetLastError() << std::endl;
            return;
        }
        if(board.check() != 0 && board.is_draw() != 0){break;}
        while(board.current_player() == 1){
            std::cout << std::endl;
            std::cin >> player2_input;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << "Please enter Valid Input" << std::endl;
                continue;
            }else if(player2_input > 9 || player2_input <= 0){
                std::cout << "Please enter Valid Input" << std::endl;
                //board.printboard();
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << std::endl;
                continue;
            }
            board.place_item(player2_input);
            break;           
        }
        //board.printboard();
        auto data = board. send_ready_data();
        sendbuf = data.get();
        //std::cout << sendbuf << std::endl;

        iResult = send(clientSocket, sendbuf, 10,0);
        board.printboard();
        std::cout << std::endl;
        if(iResult == SOCKET_ERROR){
            std::cout << "error sending back to server." << iResult << std::endl;
            freeaddrinfo(result);
            closesocket(clientSocket);
            WSACleanup();
            return;
        }

        //std::cout << "sent from cleint to server" << std::endl;

    }

    if(board.get_game_won() == 1){
        std::cout << "Player1(S) won the game." << std::endl;
    }else if(board.get_game_won() == 2){
        std::cout << "player2(C) won the game." << std::endl;
    }else if(board.is_draw() != 0){
        std::cout << "Game ends in a draw!" << std::endl;
    }
    
    freeaddrinfo(result);
    closesocket(clientSocket);
    WSACleanup();
    return;
}
