#ifndef __BOARD_H__
#define __BOARD_H__

#include "subject.h"
class Piece;
struct coord;

struct Move{
    //If this is the first move of the moving piece
    bool firstMove; 
    coord startMove;
    coord endMove;
    bool capture;
};

class Board : public Subject {
    bool whiteTurn;
    int whiteWins;
    int blackWins;
    int draws;
    
public:
    Piece** grid[8];
    
    void move(coord start, coord end);
    void setTurn(char turn);
    char getState(coord pos);
    void printResult();
    void printBoard();
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void placePiece(char piece, coord c);
    void removePiece(coord c);
    Piece* findKing();

    Board();
    ~Board();

};

#endif
