#include "pieces.h"
#include "board.h"
#include "observer.h"
#include <iostream>
#include <vector>

using namespace std;

Board* defaultBoard(){

    Board *b = new Board;

    for(int i = 0; i < 8; i ++){
        b->placePiece('p', coord{i,6});
        b->placePiece('P', coord{i,1});
    }
    
    b->placePiece('r', coord{0,7});
    b->placePiece('n', coord{1,7});
    b->placePiece('b', coord{2,7});
    b->placePiece('q', coord{3,7});
    b->placePiece('k', coord{4,7});
    b->placePiece('b', coord{5,7});
    b->placePiece('n', coord{6,7});
    b->placePiece('r', coord{7,7});

    b->placePiece('R', coord{0,0});
    b->placePiece('N', coord{1,0});
    b->placePiece('B', coord{2,0});
    b->placePiece('Q', coord{3,0});
    b->placePiece('K', coord{4,0});
    b->placePiece('B', coord{5,0});
    b->placePiece('N', coord{6,0});
    b->placePiece('R', coord{7,0});
    
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
                        GI->grid[x][y] = new King(piece == 'K', coord{x,y});
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