#include "pieces.h"
#include "board.h"
#include <iostream>

using namespace std;

int main(){
    Board board;

    bool whiteTurn = true;

    string command;
    while(cin >> command){ //command loop
        if(command == "game"){
            string p1; //white
            string p2; //black
            cin >> p1 >> p2;
            while(cin >> command){   //game loop
                if(command == "move"){
                    string start;
                    string end;
                    cin >> start >> end;
                }else if(command == "resign"){
                
                } 
            }
        }else if(command == "setup"){
            while(cin >> command){   //setup loop
                if(command == "+"){
                    char piece;
                    string coord;
                    cin >> piece >> coord;
                }else if(command == "-"){
                    string coord;
                    cin >> coord;
                }else if(command == "="){
                    string colour;
                    cin >> colour;
                    if(colour == "black" || colour == "b" || colour == "B"){
                        whiteTurn = false;
                    }else if(colour == "white" || colour == "w" || colour == "W"){
                        whiteTurn = true;
                    }
                }else if(command == "done"){
                    break;
                }
            }
        }


    }

}