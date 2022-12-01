#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>

struct coord{
    int x;
    int y;
};

class Piece{
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

        virtual bool validMove(coord p, Board * board) = 0;
};

class Rook : Piece {
    
    public:
        Rook(bool w, coord pos); //bool iswhite position
        bool validMove(coord pos, Board * board);
        void castle();
};

class King : Piece {
    public:
        King(bool w, coord pos);
        void move(coord pos, Board * board);
        bool validMove(coord pos);
        void castle();
};


class Pawn : Piece {
    public:
        Pawn(bool w, coord pos);
        bool validMove(coord pos, Board * board);
        std::string promote(std::string piece);
};

class Bishop : Piece {
    public:
        Bishop(bool w, coord pos);
        bool validMove(coord pos, Board * board);

};

class Knight : Piece {
    public:
        Knight(bool w, coord pos);
        bool validMove(coord pos, Board * board);

class Queen : Piece {
    public:
        Queen(bool w, coord pos);
        bool validMove(coord pos, Board * board);
        };
#endif