#include "observer.h"
#include "pieces.h"
#include "board.h"
#include <iostream>
#include <string>

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

GraphicalObserver::GraphicalObserver(Board * subject): subject{subject} {
    x = new Xwindow(500, 500);
};

void GraphicalObserver::notify(){
    const int SIZE = 50;
    const int PADDING = 50;
    for(int i = 7; i >= 0; i--){         // row
        for(int j = 0; j < 8; j++){     // col
            if((i+j) % 2 != 0){
                x->fillRectangle(j*SIZE+PADDING, i*SIZE+PADDING, SIZE, SIZE, 5); //cyan
            }
            else if((i+j) % 2 == 0){
                x->fillRectangle(j*SIZE+PADDING, i*SIZE+PADDING, SIZE, SIZE, 0); //white
            }

        }
    }

    for(int i = 7; i >= 0; i--){         // row
        for(int j = 0; j < 8; j++){     // col
            coord p;
            p.x = j;
            p.y = i;

            char c = subject->getState(p);
            if(c != ' ' && c != '_'){
                x->drawString(j*SIZE+PADDING+25, 400-i*SIZE+PADDING-25, std::string(1,c));
            }
        }
    }
}