#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>
#include "board.h"
#include <vector>

class Computer{
    Board* b;
    vector<string> allValidMoves;  //strings formatted "startcoordsendcoords" ("a4e4")
    public:        
        Computer(Board* b);
        virtual ~Computer(){};
        virtual void move() = 0;
        
        
        }

class Computer1 : public Computer{
    
    public:
        void move();
}

class Computer2 : public Computer{
    vector<string> captureCheckMoves;
    public:
        void move();
}

class Computer3 : public Computer{
    public:
        void move();
}

class Computer4 : public Computer{
    public:
        void move();
}
#endif