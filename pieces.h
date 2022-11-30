#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>

struct coord{
    int x;
    int y;
};

class Piece{
    bool isWhite;
    coord position;
    public:
        virtual ~Piece() = 0;
        virtual void move(coord pos) = 0;
        virtual coord getPosition() = 0;
        virtual char getColor() = 0;
        virtual bool validMove(coord pos) = 0;
        virtual bool hasMoved() = 0;
};

class Rook : Piece {
    bool moved = false;
    public:
        Rook(bool w, coord pos); //bool iswhite position
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
        void castle();
        char getType();
};

class King : Piece {
    bool moved = false;
    public:
        King(bool w, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
        void castle();
        char getType();
};


class Pawn : Piece {
    bool moved = false;
    public:
        Pawn(bool w, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
        std::string promote(std::string piece);
        char getType();};

class Bishop : Piece {
    public:
        Bishop(bool w, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();
};

class Knight : Piece {
    public:
        Knight(bool w, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();};

class Queen : Piece {
    public:
        Queen(bool w, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();
        };
#endif