
#include<server.h>
#include<board.h>
#include<string>
#include<memory>
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

    Board board;
    int player1_input;


    while(board.check() == 0 && board.is_draw() == 0){   
        //board.printboard();
        //std::cout << std::endl;
        std::cout << "Enter position of next entry: " << std::endl; 
        while(board.current_player() == 0){
            std::cin >> player1_input;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << "Please enter Valid Input" << std::endl;
                continue;
            }else if(player1_input > 9 || player1_input <= 0){
                std::cout << "Please enter Valid Input" << std::endl;
                //board.printboard();
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << std::endl;
                continue;
            }
            board.place_item(player1_input);
            break;           
        }
        auto data = board. send_ready_data();
        sendbuf = data.get();
        //std::cout << sendbuf << std::endl;


        iResult = send(clientSocket, sendbuf,10, 0);
        board.printboard();
        std::cout << std::endl;
        if(board.check() != 0 && board.is_draw() != 0){break;}
        //delete[] sendbuf;
        
        if(iResult == SOCKET_ERROR){
            std::cerr << "cound't send." << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            closesocket(listenSocket);
            WSACleanup();
            return;
        }

        //std::cout << "message sent." << std::endl;
        std::cout << "Wait for other player." << std::endl;

        iResult = recv(clientSocket, receivebuf, 10, 0);
        if(iResult > 0){
            receivebuf[iResult] = '\0';
            //char* temp = new char[9];
            std::shared_ptr<char[]> temp(new char[9],[](char* ptr){delete[] ptr;});
            memcpy(temp.get(), receivebuf, 9);
            board.set_game(temp);
            board.set_turns(receivebuf[9] - '0');
            board.printboard();
            std::cout << std::endl;

            //std::cout << "bytes received: " << iResult << " Message: " << receivebuf <<std::endl;
        }else if(iResult == 0){
            std::cout << "connection closing." << std::endl;
        }else{
            std::cerr << "rcv failed." << WSAGetLastError() << std::endl;
        }
        //break;
    }

    if(board.get_game_won() == 1){
            std::cout << "Player1(S) won the game." << std::endl;
        }else if(board.get_game_won() == 2){
            std::cout << "player2(C) won the game." << std::endl;
        }else if(board.is_draw() != 0){
            std::cout << "Game ends in a draw!" << std::endl;
        }



    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    return;
}