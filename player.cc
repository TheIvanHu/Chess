#include "player.h"
#include "board.h"
#include "pieces.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool checkEnd(double &whiteScore, double &blackScore, Board* b){
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
                    return true;
}


bool Human::move(double &whiteScore, double &blackScore){

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
                    bool endGame = checkEnd(whiteScore, blackScore, b);
                    if(!endGame){
                        return endGame;
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

bool Computer1::move(double &whiteScore, double &blackScore){
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


                    }catch(std::string error){
                        
                    }
                }
            }
        }
    }
    if(allValidMoves.size() == 0){
        b->printBoard();           
        return checkEnd(whiteScore, blackScore, b);

    }
    srand(time(NULL));
    int r = rand() % allValidMoves.size();
    string m = allValidMoves[r];
    try{
    b->move(coord{m.at(0) - '0', m.at(1) - '0'}, 
            coord{m.at(2) - '0', m.at(3) - '0'});
    }catch(std::string error){

    }
    b->printBoard();
    bool end = checkEnd(whiteScore, blackScore, b);
    if(!end){
        return end;
    }
    cout << (b->getTurn() == 'w' ? "White" : "Black") << "'s turn: " <<endl;
    return true;
    }
}
}

bool Computer2::move(double &whiteScore, double &blackScore){
    string command;
    int greatestMoveScore = 0;
    while(cin >> command){
    if(command == "move"){
    allValidMoves.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    int curMoveScore = 0;
                    try{
                        b->move(coord{i,j}, coord{k,l});
                        if((b->getState(coord{k,l}) <= 90 && b->getState(coord{k,l}) >= 65)== (b->getTurn()=='w')){
                            curMoveScore++;
                        }if((b->isCheck('w'))||b->isCheck('b')){
                            curMoveScore++;
                        }if(b->isCheckmate('w')||b->isCheckmate('b')){
                            curMoveScore = 10;
                        }
                        
                        b->undo();
                        if(curMoveScore > greatestMoveScore){
                            allValidMoves.clear();
                            allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));
                        }else if(curMoveScore == greatestMoveScore){
                            allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));
                        }


                    }catch(std::string error){
                        
                    }
                }
            }
        }
    }
    if(allValidMoves.size() == 0){
        b->printBoard();           
        return checkEnd(whiteScore, blackScore, b);
    }
    srand(time(NULL));
    int r = rand() % allValidMoves.size();
    string m = allValidMoves[r];
    try{
    b->move(coord{m.at(0) - '0', m.at(1) - '0'}, 
            coord{m.at(2) - '0', m.at(3) - '0'});
    }catch(std::string error){

    }
    b->printBoard();   
    bool end = checkEnd(whiteScore, blackScore, b);
    if(!end){
        return end;
    }        
    cout << (b->getTurn() == 'w' ? "White" : "Black") << "'s turn: " <<endl;
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

Computer2::Computer2(Board* b): Player{b}{
}