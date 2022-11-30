#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>

struct coord{
    int x;
    int y;
};

class Piece{
    bool color;     //0 white, 1 black
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
        Rook(char c, coord pos);
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
        King(char c, coord pos);
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
        Pawn(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
        std::string promote(std::string piece);
        char getType();};

class Bishop : Piece {
    public:
        Bishop(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();
};

class Knight : Piece {
    public:
        Knight(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();};

class Queen : Piece {
    public:
        Queen(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        char getType();
        };
#endif