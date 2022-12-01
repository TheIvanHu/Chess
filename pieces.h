#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>
#include "board.h"

struct coord{
    int x;
    int y;
};

class Piece{
    protected:
        coord pos;
        char type;
        bool isWhite;
        bool moved = false;
    public:
        Piece(coord pos, char type, bool isWhite);
        virtual ~Piece() = 0;
        
        void move(coord pos);
        coord getPosition();
        char getColor() ;
        char getType();
        bool hasMoved();

        virtual bool validMove(coord p, Piece *** grid) = 0;
};

class Rook : public Piece {
    
    public:
        Rook(bool w, coord pos); //bool iswhite position
        bool validMove(coord p, Piece *** grid);
        void castle();
};

class King : public Piece {
    public:
        King(bool w, coord pos);
        void move(coord pos, Board * board);
        bool validMove(coord p, Piece *** grid);
        void castle();
};


class Pawn : public Piece {
    public:
        Pawn(bool w, coord pos);
        bool validMove(coord p, Piece *** grid);
        void promote(std::string piece);
};

class Bishop : public Piece {
    public:
        Bishop(bool w, coord pos);
        bool validMove(coord p, Piece *** grid);

};

class Knight : public Piece {
    public:
        Knight(bool w, coord pos);
        bool validMove(coord p, Piece *** grid);
};
class Queen : public Piece {
    public:
        Queen(bool w, coord pos);
        bool validMove(coord p, Piece *** grid);
};

#endif