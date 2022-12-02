#include "pieces.h"
#include "board.h"
#include "observer.h"
#include <iostream>
#include <vector>

using namespace std;

Board defaultBoard(){
    Board b ;
    
    for(int i = 0; i < 8; i ++){
        b.grid[6][i] = new Pawn(0, coord{i,6});
        b.grid[1][i] = new Pawn(1, coord{i,1});
    }
    
    b.grid[0][0] = new Rook(0, coord{0,0});
    b.grid[0][1] = new Knight(0, coord{1,0});
    b.grid[0][2] = new Bishop(0, coord{2,0});
    b.grid[0][3] = new Queen(0, coord{3,0});
    b.grid[0][4] = new King(0, coord{4,0});
    b.grid[0][5] = new Bishop(0, coord{5,0});
    b.grid[0][6] = new Knight(0, coord{6,0});
    b.grid[0][7] = new Rook(0, coord{7,0});

    b.grid[7][0] = new Rook(1, coord{0,0});
    b.grid[7][1] = new Knight(1, coord{1,0});
    b.grid[7][2] = new Bishop(1, coord{2,0});
    b.grid[7][3] = new Queen(1, coord{3,0});
    b.grid[7][4] = new King(1, coord{4,0});
    b.grid[7][5] = new Bishop(1, coord{5,0});
    b.grid[7][6] = new Knight(1, coord{6,0});
    b.grid[7][7] = new Rook(1, coord{7,0});

    return b;
}

int main(){
    Board board;
    vector<Observer *> obs;
    bool whiteTurn = true;

    string command;
    while(cin >> command){ //command loop
        if(command == "game"){
            string p1; //white
            string p2; //black
            board = defaultBoard();
            TextObserver * newOb = new TextObserver(&board);
            board.attach(newOb);
            obs.emplace_back(newOb);
            board.printBoard();


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