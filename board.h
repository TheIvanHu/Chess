#ifndef __BOARD_H__
#define __BOARD_H__

#include "subject.h"
#include "pieces.h"
#include <vector>
class Piece;

struct Move{
    //If this is the first move of the moving piece
    bool firstMove; 
    coord start;
    coord end;
    bool capture;
};

class Board : public Subject {
    std::vector<Move> moves;
    char turn;
    Piece** grid[8];
    std::vector<Piece *> captured;

public:
    
    void move(coord start, coord end);
    void undo();
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
