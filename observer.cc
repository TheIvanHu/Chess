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
    const int SIZE = 50;
    const int PADDING = 50;
    x = new Xwindow(500, 500);
    for(int i = 0; i < 8; i++){
        x->drawString(PADDING-20, SIZE*(i+1)-25+PADDING, std::to_string(8-i));
        x->drawString(SIZE*(i+1)-25+PADDING, PADDING+SIZE*8+20, std::string(1,'a'+i));
    }
};

void GraphicalObserver::notify(){
    const int SIZE = 50;
    const int PADDING = 50;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
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