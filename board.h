#ifndef __BOARD_H__
#define __BOARD_H__
#include "subject.h"

class Piece;
struct coord;

class Board : Subject{
    Piece** grid;
    char turn;
    int whiteWin;
    int blackWin;
    int draw;
public:
    void move(coord start, coord end);
    void setTurn(char turn);
    char getState(coord pos);
    void printResult();
    Board();
    ~Board();

};

#endif
