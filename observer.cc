#include "observer.h"
#include "pieces.h"
#include "board.h"
#include "window.h"
#include <iostream>

struct coord;

void TextObserver::notify(){
    for(int i = 0; i < 8; i++){         // row
        for(int j = 0; j < 8; j++){     // col
            coord p;
            p.x = j;
            p.y = i;
            std::cout << 8 - i << " " << subject.getState(p) << std::endl;
        }
    }
    std::cout << std::endl << "  abcdefgh";
}

void GraphicalObserver::notify(){

}