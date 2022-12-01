#ifndef __BOARD_H__
#define __BOARD_H__
#include "subject.h"

class Piece;
struct coord;

class Board : Subject{
    bool whiteTurn;
    int whiteWins;
    int blackWins;
    int draws;
public:
    Piece*** grid;

    void move(coord start, coord end);
    void setTurn(char turn);
    char getState(coord pos);
    void printResult();
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    Board();
    ~Board();

};

#endif
