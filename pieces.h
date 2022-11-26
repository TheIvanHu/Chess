#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>

struct coord{
    int x;
    int y;
};

class Piece{
    char color;
    coord position;
    public:
        virtual void move(coord pos);
        virtual coord getPosition();
        virtual char getColor();
        virtual bool validMove(coord pos);
        virtual bool hasMoved();
};

class Rook : Piece {
    public:
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
};

#endif