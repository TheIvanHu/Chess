#ifndef __BOARD_H__
#define __BOARD_H__

#include "subject.h"
#include "pieces.h"

class Piece;

struct Move{
    //If this is the first move of the moving piece
    bool firstMove; 
    coord startMove;
    coord endMove;
    bool capture;
};

class Board : public Subject {
    char turn;
    Piece** grid[8];

public:
    
    void move(coord start, coord end);
    void setTurn(char newTurn);
    char getState(coord pos);
    void printBoard();
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void placePiece(char piece, coord c);
    void removePiece(coord c);
    void clearBoard();
    char getTurn();
    Piece* findKing();

    Board();
    ~Board();

};

#endif
