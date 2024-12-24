#include "board.h"
#include <iostream>

    Board::Board(){
        game = new char [9];
        //char[] game = new char[9]
        input1 = 'O';
        input2 = 'X';
        turns = 0;
        for(int i = 0; i < 9; i++){
            game[i] = '#';
        }
    }

    void Board::place_item(int i){
        int index = i - 1;
        if(game[index] == '#' && (turns % 2) == 0){
            game[index] = input1;
            turns++;
        }else if(game[index] == '#' && (turns % 2) == 1){
            game[index] = input2;
            turns++;
        }
        draw++;
    }

    void Board::printboard(void){
        for(int i = 0; i < 9; i++){
            if(i % 3 == 0 && i != 0){
                std::cout<< std::endl;
            }
            std::cout << game[i];
            std::cout << " ";
        }
    }
    void Board::check(void){
        int count1 = 0;
        int count2 = 0;
        //rows
        for(int i = 0; i < 3; i++){
            count1 = 0;
            count2 = 0;
            for(int j = 0; j < 3; j++){
                if(game[3*i + j] == 'O'){
                    count1++;
                }
                if(game[3*i + j] == 'X'){
                    count2++;
                }
                if(count1 == 3){
                    gamewon = 1;
                }
                if(count2 == 3){
                    gamewon = 2;
                }
            }
        }

        //columns
        count1 = 0;
        count2 = 0;
        for(int i = 0; i < 3; i++){
            count1 = 0;
            count2 = 0;
            for(int j = 0; j < 3; j++){
                if(game[i + 3*j] == 'X'){
                    count2++;
                }else if(game[i + 3*j] == 'O'){
                    count1++;
                }
                if(count1 == 3){
                    gamewon = 1;
                }
                if(count2 == 3){
                    gamewon = 2;
                }
            }
        }
        
        count1 = 0;
        count2 = 0;
        //diagonals
        for(int i = 0, j = 0; i < 3, j < 3; i++, j++){
            if(game[3*i+j] == 'O'){
                count1++;
            }
            if(game[3*i+j] == 'X'){
                count2++;
            }
        }
        if(count1 == 3){
            gamewon = 1;
            count1 = 0;
        }
        if(count2 == 3){
            gamewon = 2;
        }
        count1 = 0;
        count2 = 0;
        for(int i = 0, j = 2; j >= 0, i < 3; j--,i++){
            if(game[3*i + j] == 'O'){
                count1++;
            }else if(game[3*i + j] == 'X'){
                count2++;
            }
        }
        if(count1 == 3){
            gamewon = 1;
        }
        if(count2 == 3){
            gamewon = 2;
        }
        return;
    }

    int Board::get_game_won(void){
        return gamewon;
    }
    int Board::get_turn(void){
        return turns % 2;
    }
    int Board::get_draw(void){
        return draw;
    }