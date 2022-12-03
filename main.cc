#include "pieces.h"
#include "board.h"
#include "observer.h"
#include <iostream>
#include <vector>

using namespace std;

Board* defaultBoard(){

    Board *b = new Board;

    for(int i = 0; i < 8; i ++){
        b->grid[i][6] = new Pawn(0, coord{i,6});
        b->grid[i][1] = new Pawn(1, coord{i,1});
    }
    
    b->grid[0][7] = new Rook(0, coord{0,7});
    b->grid[1][7] = new Knight(0, coord{1,7});
    b->grid[2][7] = new Bishop(0, coord{2,7});
    b->grid[3][7] = new Queen(0, coord{3,7});
    b->grid[4][7] = new King(0, coord{4,7});
    b->grid[5][7] = new Bishop(0, coord{5,7});
    b->grid[6][7] = new Knight(0, coord{6,7});
    b->grid[7][7] = new Rook(0, coord{7,7});

    b->grid[0][0] = new Rook(1, coord{0,0});
    b->grid[1][0] = new Knight(1, coord{1,0});
    b->grid[2][0] = new Bishop(1, coord{2,0});
    b->grid[3][0] = new Queen(1, coord{3,0});
    b->grid[4][0] = new King(1, coord{4,0});
    b->grid[5][0] = new Bishop(1, coord{5,0});
    b->grid[6][0] = new Knight(1, coord{6,0});
    b->grid[7][0] = new Rook(1, coord{7,0});


    return b;

}

int main(){
    Board *board;
    vector<Observer *> obs;
    board = defaultBoard();
    TextObserver * newOb = new TextObserver(board);
    board->attach(newOb);
    obs.emplace_back(newOb);
    bool whiteTurn = true;

    string command;
    
    while(cin >> command){ //command loop
    
        if(command == "game"){
            string p1; //white
            string p2; //black
            
            board->printBoard();


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
                    string pos;
                    int x, y;
                    cin >> piece >> pos;
                    
                    x = pos.at(0) - 'a';
                    y = pos.at(1) - '1';
                    if(piece == 'K' || piece == 'k'){
                        board->grid[x][y] = new King(piece == 'K', coord{x,y});
                    }else if(piece == 'Q' || piece == 'q'){
                        board->grid[x][y] = new Queen(piece <= 90 && piece >= 65, coord{x,y});
                    }else if(piece == 'B' || piece == 'b'){
                        board->grid[x][y] = new Bishop(piece <= 90 && piece >= 65, coord{x,y});
                    }else if(piece == 'N' || piece == 'n'){
                        board->grid[x][y] = new Knight(piece <= 90 && piece >= 65, coord{x,y});
                    }else if(piece == 'R' || piece == 'r'){
                        board->grid[x][y] = new Rook(piece <= 90 && piece >= 65, coord{x,y});
                    }else if(piece == 'P' || piece == 'p'){
                        board->grid[x][y] = new Pawn(piece <= 90 && piece >= 65, coord{x,y});
                    }

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