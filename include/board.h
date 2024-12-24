#ifndef BOARD_H
#define BOARD_H
class Board{
private:
    char* game;
    size_t game_size = 9;
    //char[] game = new char[9]
    char input1 = 'X';
    char input2 = 'O';
    int turns = 0;
    int gamewon = 0;
    //int draw = 0;
public:
    Board();
    void place_item(int index);
    void printboard(void);
    int check(void);
    int get_game_won(void);
    int current_player(void);
    int is_draw(void);
    void set_game(char* game_update);
    char* get_game(void);
    int get_turns(void);
    const char* send_ready_data(void);
    void set_turns(int a);
};

#endif 