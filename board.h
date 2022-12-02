#ifndef __BOARD_H__
#define __BOARD_H__

#include "subject.h"
class Piece;
struct coord;

struct Move{
    //first move of the moving piece
    bool firstMove;
    
};
class Board : public Subject {
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
    void printBoard();
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    Piece* findKing();
    Board();
    ~Board();

};

#endif
