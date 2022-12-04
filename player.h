#ifndef __PIECES_H__
#define __PIECES_H__

#include <vector>
#include <string>
#include "board.h"
#include "pieces.h"

class Player{
    Board* b;
    vector<string> allValidMoves;  //strings formatted "startcoordsendcoords" ("a4e4")
    public:        
        Player(Board* b);
        virtual ~Player(){};
        virtual void move() = 0;
        
        
        };

class Computer1 : public Player{

    public:
        void move();
};

class Computer2 : public Player{
    vector<string> captureCheckMoves;
    public:
        void move();
};

class Computer3 : public Player{
    public:
        void move();
};

class Computer4 : public Player{
    public:
        void move();
};
#endif