#include "observer.h"
#include "pieces.h"
#include "board.h"
#include <iostream>

struct coord;

TextObserver::TextObserver(Board * subject): subject{subject} {};


void TextObserver::notify(){
    for(int i = 7; i >= 0; i--){         // row
    out << i + 1 << " ";
        for(int j = 0; j < 8; j++){     // col
            coord p;
            p.x = j;
            p.y = i;
            out << subject->getState(p);
        }
        out << std::endl;
    }
    out << "  abcdefgh" << std::endl;
}

void GraphicalObserver::notify(){

}