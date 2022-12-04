#ifndef __PIECES_H__
#define __PIECES_H__

#include <string>
#include "board.h"

class Board;

class Computer{
    Board* b;
    vector<string> allValidMoves;
    public:        
        Computer(Board* b);
        virtual ~Computer(){};
        virtual move();
        
        
        }

class Computer1 : public Computer{

}

class Computer2 : public Computer{

}

class Computer3 : public Computer{

}

class Computer4 : public Computer{

}
#endif