#include "pieces.h"
#include "board.h"
#include "observer.h"
#include <iostream>
#include <vector>

using namespace std;

void setDefaultBoard(Board* b){

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
    
}

int main(){
    double whiteScore = 0;
    double blackScore = 0;

    Board *board = new Board;
    vector<Observer *> obs;
    TextObserver * newOb = new TextObserver(board);
    board->attach(newOb);
    obs.emplace_back(newOb);
    bool setBoard = false;      //if the board has been setup
    string command;
    
    while(cin >> command){          //command loop
        if(command == "game"){
            string p1;              //white
            string p2;              //black
            if(!setBoard){
                setDefaultBoard(board);
                board->setTurn('w');
            }
            board->printBoard();

            cin >> p1 >> p2;
            cout << "White's turn: " <<endl;
            while(cin >> command){   //game loop
                
                if(command == "move"){
                    string start;
                    string end;
                    cin >> start >> end;    
                    
                    try{
                        board->move(coord{start.at(0) - 'a',start.at(1) - '1'}, 
                                    coord{end.at(0) - 'a',end.at(1) - '1'});        //auto converts chess move (e4) to coords
                        board->printBoard();           
                    }catch(string error){
                        cout << error << endl;
                    }
                   
                    if(board->isCheckmate(board->getTurn())){
                        cout << "Checkmate! " << (board->getTurn() == 'w' ? "Black" : "White") << " wins!" << endl;
                        if(board->getTurn() == 'w'){
                            blackScore++;
                        }else{
                            whiteScore++;
                        }
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        board->resetBoard();
                        setDefaultBoard(board);
                        break;
                    }
                    else if(board->isStalemate(board->getTurn())){
                        cout << "Stalemate!" << endl;
                        whiteScore += 0.5;
                        blackScore += 0.5;
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        board->resetBoard();
                        setDefaultBoard(board);
                        break;
                    }
                }else if(command =="undo"){
                    board->undo();
                    board->printBoard();
                }else if(command == "resign"){
                    cout << (board->getTurn() == 'w' ? "White" : "Black") << " Resigns, " << endl;
                    cout << (board->getTurn() == 'w' ? "Black" : "White") << " wins!" << endl;
                    if(board->getTurn() == 'w'){
                        blackScore++;
                    }else{
                        whiteScore++;
                    }
                    cout << "SCORE" << endl;
                    cout << "White: " << whiteScore << endl;
                    cout << "Black: " << blackScore << endl;
                    break;
                }
                cout << (board->getTurn() == 'w' ? "White" : "Black") << "'s turn: " <<endl; 
            }
        }else if(command == "setup"){
            setBoard = true;
            while(cin >> command){   //setup loop
                if(command == "+"){
                    char piece;
                    string pos;
                    cin >> piece >> pos;

                    board->placePiece(piece,coord{pos.at(0) - 'a',
                                                  pos.at(1) - '1'});
                    board->printBoard();
                }else if(command == "-"){
                    string pos;
                    cin >> pos;
                    board->removePiece(coord{pos.at(0) - 'a',
                                             pos.at(1) - '1'});
                    board->printBoard();
                }else if(command == "="){
                    string colour;
                    cin >> colour;
                    if(colour == "black" || colour == "b" || colour == "B"){
                        board->setTurn('b');
                    }else if(colour == "white" || colour == "w" || colour == "W"){
                        board->setTurn('w');
                    }
                }else if(command == "done"){
                    board->printBoard();
                    if(!board->setupCheck()){
                        cout << "Invalid board setup" << endl;
                    }
                    else break;
                }
            }
        }


    }
    delete board;
    cout << "Final Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
}