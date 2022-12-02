#include "observer.h"
#include "pieces.h"
#include "board.h"
#include <iostream>

struct coord;

void TextObserver::notify(){
    for(int i = 0; i < 8; i++){         // row
    out << 8 - i << " ";
        for(int j = 0; j < 8; j++){     // col
            coord p;
            p.x = j;
            p.y = i;
            out << subject->getState(p);
        }
        out << std::endl;
    }
    out << std::endl << "  abcdefgh";
}

void GraphicalObserver::notify(){

}