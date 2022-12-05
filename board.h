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
    bool castle;
    bool promote;
    bool enpassant;
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
    bool isCheck(char color);
    bool isCheckmate(char color);
    bool isStalemate(char color);
    bool isCapturable(coord c); //purely used for computers to tell when a piece can be saved from capture

    void placePiece(char piece, coord c);
    void removePiece(coord c);
    void clearBoard();
    char getTurn();
    bool setupCheck();
    void resetBoard();


    Piece* findKing(char color);

    Board();
    ~Board();

};

#endif
