#ifndef BOARD_H
#define BOARD_H
class Board{
private:
    char* game;
    //char[] game = new char[9]
    char input1 = 'X';
    char input2 = 'O';
    int turns = 0;
    int gamewon = 0;
    int draw = 0;
public:
    Board();
    void place_item(int index);
    void printboard(void);
    void check(void);
    int get_game_won(void);
    int get_turn(void);
    int get_draw(void);
};

#endif 