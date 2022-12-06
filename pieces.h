#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>
class Board;

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
        virtual ~Piece(){};
        
        void move(coord pos);
        coord getPosition();
        char getColor();
        char getType();
        bool hasMoved();
        void setMoved(bool m);

        virtual bool validMove(coord p, Piece *** grid) = 0;
};

class Rook : public Piece {
    
    public:
        Rook(bool w, coord pos); //bool iswhite position
        ~Rook(){};
        bool validMove(coord p, Piece *** grid);
        void castle();
};

class King : public Piece {
    public:
        King(bool w, coord pos);
        ~King(){};
        void move(coord pos, Board * board);
        bool validMove(coord p, Piece *** grid);
        void castle();
};


class Pawn : public Piece {
    public:
        Pawn(bool w, coord pos);
        ~Pawn(){};
        bool validMove(coord p, Piece *** grid);
        void promote(std::string piece);
};

class Bishop : public Piece {
    public:
        Bishop(bool w, coord pos);
        ~Bishop(){};
        bool validMove(coord p, Piece *** grid);

};

class Knight : public Piece {
    public:
        Knight(bool w, coord pos);
        ~Knight(){};
        bool validMove(coord p, Piece *** grid);
};
class Queen : public Piece {
    public:
        Queen(bool w, coord pos);
        ~Queen(){};
        bool validMove(coord p, Piece *** grid);
};

#endif
