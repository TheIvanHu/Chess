#include "player.h"
#include "board.h"
#include "pieces.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


bool Human::move(double whiteScore, double blackScore){

    string command;
    cin >> command;
    if(command == "move"){
                    string start;
                    string end;
                    cin >> start >> end;    
                    
                    try{
                        b->move(coord{start.at(0) - 'a',start.at(1) - '1'}, 
                                    coord{end.at(0) - 'a',end.at(1) - '1'});        //auto converts chess move (e4) to coords
                        b->printBoard();           
                    }catch(string error){
                        cout << error << endl;
                    }
                   
                   if(b->isCheckmate(b->getTurn())){
                        cout << "Checkmate! " << (b->getTurn() == 'w' ? "Black" : "White") << " wins!" << endl;
                        if(b->getTurn() == 'w'){
                            blackScore++;
                        }else{
                            whiteScore++;
                        }
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        b->resetBoard();
                        return false;
                    }
                    else if(b->isStalemate(b->getTurn())){
                        cout << "Stalemate!" << endl;
                        whiteScore += 0.5;
                        blackScore += 0.5;
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        b->resetBoard();
                        return false;
                    }
                    
                }else if(command =="undo"){
                    b->undo();
                    b->printBoard();
                }else if(command == "resign"){
                    cout << (b->getTurn() == 'w' ? "White" : "Black") << " Resigns, " << endl;
                    cout << (b->getTurn() == 'w' ? "Black" : "White") << " wins!" << endl;
                    if(b->getTurn() == 'w'){
                        blackScore++;
                    }else{
                        whiteScore++;
                    }
                    cout << "SCORE" << endl;
                    cout << "White: " << whiteScore << endl;
                    cout << "Black: " << blackScore << endl;
                    return false;
                }
                cout << (b->getTurn() == 'w' ? "White" : "Black") << "'s turn: " <<endl;
                return true; 
}

bool Computer1::move(double whiteScore, double blackScore){
    string command;
    while(cin >> command){
    if(command == "move"){
    allValidMoves.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    try{
                        b->move(coord{i,j}, coord{k,l});
                        b->undo();
                        allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));


                    }catch(string error){
                        
                    }
                }
            }
        }
    }
    if(allValidMoves.size() == 0){
        if(b->isCheckmate(b->getTurn())){
                        cout << "Checkmate! " << (b->getTurn() == 'w' ? "Black" : "White") << " wins!" << endl;
                        if(b->getTurn() == 'w'){
                            blackScore++;
                        }else{
                            whiteScore++;
                        }
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        b->resetBoard();
                        return false;
                    }
                    else if(b->isStalemate(b->getTurn())){
                        cout << "Stalemate!" << endl;
                        whiteScore += 0.5;
                        blackScore += 0.5;
                        cout << "SCORE" << endl;
                        cout << "White: " << whiteScore << endl;
                        cout << "Black: " << blackScore << endl;
                        b->resetBoard();
                        return false;
                    }
                    return false;
    }
    srand(time(NULL));
    int r = rand() % allValidMoves.size();
    string m = allValidMoves[r];
    b->move(coord{m.at(0) - '0', m.at(1) - '0'}, 
            coord{m.at(2) - '0', m.at(3) - '0'});

    b->printBoard();           
    cout << (b->getTurn() == 'w' ? "White" : "Black") << "'s turn: " <<endl;
    cout << m << endl;
    return true;
    }
}
}
Player::Player(Board * b) : b{b}{
}

Human::Human(Board* b) : Player{b}{
}

Computer1::Computer1(Board* b): Player{b}{
}