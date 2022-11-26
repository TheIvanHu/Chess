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
        Piece(char c, coord pos);
        virtual ~Piece();        
        virtual void move(coord pos);
        virtual coord getPosition();
        virtual char getColor();
        virtual bool validMove(coord pos);
        virtual bool hasMoved();
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
};

class Bishop : Piece {
    public:
        Bishop(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
};

class Knight : Piece {
    public:
        Knight(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
};

class Queen : Piece {
    public:
        Queen(char c, coord pos);
        void move(coord pos);
        coord getPosition();
        char getColor();
        bool validMove(coord pos);
        bool hasMoved();
};
#endif