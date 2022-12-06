#include "player.h"
#include "board.h"
#include "pieces.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

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
    while(cin >> command){
    if(command == "move"){
                    string start;
                    string end;
                    while(cin >> start){    
                    if(start.at(0) - 'a' <= 'h' -'a' &&
                    start.at(0) - 'a' >= 'a' -'a' &&
                    start.at(1) - '1' <= '8' -'1' &&
                    start.at(1) - '1' >= '1' -'1'){
                    while(cin >> end){    
                    if(end.at(0) - 'a' <= 'h' -'a' &&
                    end.at(0) - 'a' >= 'a' -'a' &&
                    end.at(1) - '1' <= '8' -'1' &&
                    end.at(1) - '1' >= '1' -'1'){

                    
                    try{
                        b->move(coord{start.at(0) - 'a',start.at(1) - '1'}, 
                                    coord{end.at(0) - 'a',end.at(1) - '1'});        //auto converts chess move (e4) to coords
                        b->printBoard();           
                    }catch(string error){
                        cout << error << endl;
                        continue;
                    }
                    bool endGame = checkEnd(whiteScore, blackScore, b);
                    if(!endGame){
                        return endGame;
                    }
                    break;
                    }
    }
                    }}
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
                        b->undo();  //check all possible moves, if valid, undo and add to allValidMoves
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
        //if no possible moves, either checkmate or stalemate
    }
    srand(time(NULL));                              //generates a completely random move
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
return true;

}

bool Computer2::move(double &whiteScore, double &blackScore){
    string command;
    char colorAlly = b->getTurn(); //'b' or 'w'
    char colorEnemy;
    if(colorAlly == 'b'){
        colorEnemy ='w';
    } else{
        colorEnemy = 'b';
    }

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
                        if((b->getState(coord{k,l}) <= 122 && b->getState(coord{k,l}) >= 97) == (colorEnemy =='b')){
                            curMoveScore++; //check that a piece of colorEnemy is on the end square (capture)
                        }
                        b->move(coord{i,j}, coord{k,l});
                        if((b->isCheck(colorEnemy))){
                            curMoveScore++;
                        }if(b->isCheckmate(colorEnemy)){
                            curMoveScore = 10;
                        }
                        
                        b->undo();
                        if(curMoveScore > greatestMoveScore){ // if a move found has a larger MoveScore, the vector is cleared and given a new move
                            allValidMoves.clear();
                            allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));
                            greatestMoveScore = curMoveScore;
                        }else if(curMoveScore == greatestMoveScore){ // if equal, its added to the vector
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
return true;

}

bool Computer3::move(double &whiteScore, double &blackScore){
    string command;
    char colorAlly = b->getTurn();
    char colorEnemy;
    if(colorAlly == 'b'){
        colorEnemy ='w';
    } else{
        colorEnemy = 'b';
    }
    int greatestMoveScore = 0;
    while(cin >> command){
    if(command == "move"){
    allValidMoves.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    int curMoveScore = 0;
                    int capturableStart = 0;
                    int capturableEnd = 0; // how many pieces are capturable before and after
                    try{
                        for(int m = 0; m < 8; m++){
                            for(int n = 0; n < 8; n++){
                                if(
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65) == (colorAlly=='w'))
                                &&  //Check if m,n is an ally square and then check if its capturable
                                b->isCapturable(coord{m,n})
                                ){
                                    capturableStart++;
                                }
                            }
                        }
                        if((b->getState(coord{k,l}) <= 122 && b->getState(coord{k,l}) >= 97) == (colorEnemy =='b')){
                            curMoveScore++; //check that a piece of colorEnemy is on the end square (capture)
                        }
                        b->move(coord{i,j}, coord{k,l});

                        for(int m = 0; m < 8; m++){
                            for(int n = 0; n < 8; n++){
                                if( //Check if m,n is an ally square and then check if its capturable
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65)== (colorAlly=='w'))
                                &&
                                b->isCapturable(coord{m,n})){
                                    capturableEnd++;
                                }
                            }
                        }

                        if(b->isCheck(colorEnemy)){
                            curMoveScore++;
                        }if(b->isCheckmate(colorEnemy)){
                            curMoveScore = 10;
                        }if(capturableStart > capturableEnd){
                            curMoveScore++; // check that less of your pieces are capturable at the end of the move than before.
                        }
                        
                        b->undo();
                        if(curMoveScore > greatestMoveScore){
                            allValidMoves.clear();
                            allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));
                            greatestMoveScore = curMoveScore;
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
return true;

}

bool Computer4::move(double &whiteScore, double &blackScore){
    const map<char, int> pieceValues = {
    {'p',1},
    {'P',1},
    {'b',3},
    {'B',3},
    {'n',3},
    {'N',3},
    {'r',5},
    {'R',5},
    {'q',9},
    {'Q',9},
};
    char colorAlly = b->getTurn();
    char colorEnemy;
    if(colorAlly == 'b'){
        colorEnemy ='w';
    } else{
        colorEnemy = 'b';
    }
    string command;
    int greatestMoveScore = -2147483648;
    while(cin >> command){
    if(command == "move"){
    allValidMoves.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    int curMoveScore = 0;
                    int capturableStartAlly = 0;
                    int capturableEndAlly = 0; // how many pieces are capturable before and after
                    int capturableStartEnemy = 0;
                    int capturableEndEnemy = 0;
                    bool capture = false;
                    try{
                        for(int m = 0; m < 8; m++){
                            for(int n = 0; n < 8; n++){
                                if(
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65) == (colorAlly=='w'))
                                &&  //Check if m,n is an ally square and then check if its capturable
                                b->isCapturable(coord{m,n})
                                ){
                                    auto it = pieceValues.find(b->getState(coord{m,n}));
                                    capturableStartAlly += ( it->second);
                                }
                                if( //Check if m,n is an enemy square and then check if its capturable
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65) == (colorEnemy=='w'))
                                &&
                                b->isCapturable(coord{m,n})){
                                    auto it = pieceValues.find(b->getState(coord{m,n}));
                                    capturableStartEnemy += (it->second);                   
                              }
                            }
                        }
                        if((b->getState(coord{k,l}) <= 122 && b->getState(coord{k,l}) >= 97) == (colorEnemy =='b')){
                            //check that a piece of colorEnemy is on the end square (capture)
                            auto it = pieceValues.find(b->getState(coord{k,l}));
                            curMoveScore += (10 * it->second);
                            capture = true;
                        }
                        b->move(coord{i,j}, coord{k,l});
                        if(capture && b->isCapturable(coord{k,l})){
                            //trading pieces
                            auto it = pieceValues.find(b->getState(coord{k,l}));
                            curMoveScore -= (8 * it->second);
                        }
                        for(int m = 0; m < 8; m++){
                            for(int n = 0; n < 8; n++){
                                if( //Check if m,n is an ally square and then check if its capturable
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65) == (colorAlly=='w'))
                                &&
                                b->isCapturable(coord{m,n})){
                                    auto it = pieceValues.find(b->getState(coord{m,n}));
                                    capturableEndAlly += it->second;                                  
                                    }
                                if( //Check if m,n is an enemy square and then check if its capturable
                                ((b->getState(coord{m,n}) <= 90 && b->getState(coord{m,n}) >= 65) == (colorEnemy=='w'))
                                &&
                                b->isCapturable(coord{m,n})){
                                    auto it = pieceValues.find(b->getState(coord{m,n}));
                                    capturableEndEnemy += it->second; 
                                }
                            }
                        }

                        if(b->isCheck(colorEnemy)){
                            curMoveScore += 7;
                        }if(b->isCheckmate(colorEnemy)){
                            curMoveScore = 999999;
                        }if((b->getState(coord{i,j})=='k'||b->getState(coord{i,j})=='K')&&!b->getPiece(coord{i,j})->hasMoved()){
                            curMoveScore -= 7; //if the king has moved
                        }
                        curMoveScore+=(capturableStartAlly - 2 * capturableEndAlly);
                        curMoveScore+=(capturableEndEnemy - capturableStartEnemy);

                        b->undo();
                        if(curMoveScore > greatestMoveScore){
                            allValidMoves.clear();
                            allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));
                            greatestMoveScore = curMoveScore;
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
return true;

}

Player::Player(Board * b) : b{b}{
}

Human::Human(Board* b) : Player{b}{
}

Computer1::Computer1(Board* b): Player{b}{
}

Computer2::Computer2(Board* b): Player{b}{
}

Computer3::Computer3(Board *b) : Player{b}{
}

Computer4::Computer4(Board *b) : Player{b}{
}