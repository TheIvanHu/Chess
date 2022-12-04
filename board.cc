#include "board.h"
#include "subject.h"
#include "pieces.h"
#include <iostream>
#include <cctype>

void Board::move(coord start, coord end){
    Piece* p1 = grid[start.x][start.y];
    Piece* p2 = grid[end.x][end.y];
    //checking p1 isn't a null pointer, the start and end 
    if(p1 == nullptr || start.y < 0 || start.y > 7 || start.x < 0 || start.x > 7 || end.y < 0 || end.y > 7 || end.x < 0 || end.x > 7){
        throw std::string("Move out of bounds."); 
    }
    if( !p1->validMove(end, grid) ){
        throw std::string("Invalid Move.");
    }
    if(((start.x == end.x) && (start.y == end.y))){
        throw std::string("You must move piece from starting square.");
    }
    if(p1->getColor() != turn){
        throw std::string("Not your turn.");
    }
    if((p2 && (p2->getColor() == p1->getColor()))){
        throw std::string("Space is already occupied by one of your pieces.");
    }

    bool castle = false;
    bool promote = false;
    bool enpassant = false;

    if((p1->getType() == 'k') || (p1->getType() == 'K')){
        if(end.x == (start.x + 2)){
            try{
                //check for check in the middle
                this->move(start, coord{start.x + 1, start.y});
                this->undo();
                castle = true;                
            }  
            catch(std::string error){throw error;}
        }
        if(end.x == (start.x - 2)){
            try{
                //check for check in the middle
                this->move(start, coord{start.x - 1, start.y});
                this->undo();
                castle = true;                
            }  
            catch(std::string error){throw error;}
        }
    }

    if(((p1->getType() == 'p') || (p1->getType() == 'P')) && ((end.y == 0) || (end.y == 7))){
        promote = true;
        char p;
        std::cin >> p;
        captured.emplace_back(p1);
        
        if(p == 'Q' || p == 'q'){
            p1 = new Queen(turn == 'w', start);
        }
        else if(p == 'B' || p == 'b'){
            p1 = new Bishop(turn == 'w', start);
        }
        else if(p == 'N' || p == 'n'){
            p1 = new Knight(turn == 'w', start);
        }
        else if(p == 'R' || p == 'r'){
            p1 = new Rook(turn == 'w', start);
        }
        p1->setMoved(true);
    }
    //En Passant 
    if(((p1->getType() == 'p') || (p1->getType() == 'P')) && ((start.x == end.x + 1) || (start.x == end.x - 1) ) &&
    !grid[end.x][end.y]){
        if((grid[end.x][start.y])){
            Move m = moves.at(moves.size() - 1);
            if(m.firstMove && (m.end.x == end.x) && (m.end.y = start.y)){
                enpassant = true;
            }
            else{
                throw("Invalid Move.");
            }
        }
    }

    p1->move(end);
    grid[end.x][end.y] = p1;
    grid[start.x][start.y] = nullptr;
    //check if capture has happened
    if(p2 == nullptr){
        Move m{!p1->hasMoved(), start, end, false, castle, promote, enpassant};
        moves.emplace_back(m);
    }
    else{
        captured.emplace_back(p2);
        Move m{!p1->hasMoved(), start, end, true, castle, promote, enpassant};
        moves.emplace_back(m);
    }
    if(!p1->hasMoved()) p1->setMoved(true);
    
    if(castle){
        if(end.x == (start.x + 2)){
            p2 = grid[7][start.y];
            p2->move(coord{5,start.y});
            grid[5][start.y] = p2;
            grid[7][start.y] = nullptr;
            p2->setMoved(true);
        }
        if(end.x == (start.x - 2)){
            p2 = grid[0][start.y];
            p2->move(coord{3,start.y});
            grid[3][start.y] = p2;
            grid[0][start.y] = nullptr;
            p2->setMoved(true);
        }
    }
    if(enpassant){
        p2 = grid[end.x][start.y];
        captured.emplace_back(p2);
        grid[end.x][start.y] = nullptr;
    }

    if(this->getTurn() == 'w') this->setTurn('b');
    else this->setTurn('w');
    
    if(this->isCheck(((turn=='w')? 'b':'w'))){
        this->undo();
        throw std::string("This leaves your king in check.");
    }
    
};

void Board::undo(){
    if(moves.size() == 0) return;
    
    Move m = moves.at(moves.size() - 1);
    moves.pop_back();

    Piece* p1 = grid[m.end.x][m.end.y];
    if(m.promote){
        delete p1;
        p1 = captured.at(captured.size() - 1);
        grid[m.end.x][m.end.y] = p1;
        captured.pop_back();
    }
    if(m.firstMove){
        p1->setMoved(false);
    }
    grid[m.start.x][m.start.y] = p1;
    p1->move(m.start);
    if(m.capture){
        Piece* p2 = captured.at(captured.size() - 1);
        captured.pop_back();
        grid[m.end.x][m.end.y] = p2;
    } else{
        grid[m.end.x][m.end.y] = nullptr;
    }

    if(m.enpassant){

        Piece * p2 = captured.at(captured.size() - 1);
        grid[m.end.x][m.start.y] = p2;
        captured.pop_back();
    }
    

    if(m.castle){
        if(m.end.x == 6){
            Piece * p2 =grid[5][m.start.y];

            p2->setMoved(false);
            p2->move(coord{7, m.start.y});
            grid[7][m.start.y] = p2;
            grid[5][m.start.y] = nullptr; 
        }
        if(m.end.x == 2){
            Piece * p2 =grid[3][m.start.y];
            
            p2->setMoved(false);
            p2->move(coord{0, m.start.y});
            grid[0][m.start.y] = p2;
            grid[3][m.start.y] = nullptr; 
        }
    }
    if(turn == 'w') turn = 'b';
    else turn = 'w';
}

void Board::setTurn(char newTurn){
    turn = newTurn;
};

char Board::getState(coord pos){
    Piece* p = grid[pos.x][pos.y];
    if(p == nullptr && (pos.x + pos.y) % 2 == 0){
        return '_';
    }
    else if(p == nullptr){
        return ' ';
    }
    else{
        return p->getType();
    }
};

void Board::printBoard(){
    this->notifyObservers();
}

Piece* Board::findKing(char color){
    if(color == 'w'){
        for(int i = 0; i < 8; i++){ //find black king
            for(int j = 0; j < 8; j++){
                Piece* p = grid[i][j];
                if(p && p->getColor() == 'w' && p->getType() == 'K'){
                    return p;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 8; i++){ //find white king
            for(int j = 0; j < 8; j++){
                Piece* p = grid[i][j];
                if(p && p->getColor() == 'b' && p->getType() == 'k'){
                    return p;
                }
            }
        }
    }
    return nullptr;
}
bool Board::isCheck(char color){
    Piece* king = findKing(color);
    for(int i = 0; i < 8; i++){ //check if anything can "take" the king
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            if(p && p != king && p->validMove(king->getPosition(), grid)){
                return true;
            }
        }
    }
    return false;
}

bool Board::isCheckmate(char color){
    if(!this->isCheck(color)) return false;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            if(p && (p->getColor() == color)){
                for(int k = 0; k < 8; k++){
                    for(int l = 0; l < 8; l++){
                        coord c{k,l};
                        if(p->validMove(c, grid)){ //check if the move is valid, then check if king is in check after the move
                            try{
                                this->move(coord{i,j}, c);
                                if(!this->isCheck(color)){
                                    this->undo();                        
                                    return false;
                                }
                                this->undo();
                            }
                            catch(std::string error){}
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(char color){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    coord c{k,l};
                    if(p != nullptr && p->validMove(c, grid)){
                        try{
                            this->move(coord{i,j}, c);
                            if(!this->isCheck(color)){
                                this->undo();                        
                                return false;
                            }
                            this->undo();
                        }
                        catch(std::string error){

                        }
                    }
                }
            }
        }
    }
    return true;
}

void Board::placePiece(char piece, coord c){
    if(piece == 'K' || piece == 'k'){
        grid[c.x][c.y] = new King(piece == 'K', c);
    }
    else if(piece == 'Q' || piece == 'q'){
        grid[c.x][c.y] = new Queen(piece == 'Q', c);
    }
    else if(piece == 'B' || piece == 'b'){
        grid[c.x][c.y] = new Bishop(piece == 'B', c);
    }
    else if(piece == 'N' || piece == 'n'){
        grid[c.x][c.y] = new Knight(piece == 'N', c);
    }
    else if(piece == 'R' || piece == 'r'){
        grid[c.x][c.y] = new Rook(piece == 'R', c);
    }
    else if(piece == 'P' || piece == 'p'){
        grid[c.x][c.y] = new Pawn(piece == 'P', c);
    }
}

void Board::removePiece(coord c){
    if(grid[c.x][c.y]){
        delete grid[c.x][c.y];
        grid[c.x][c.y] = nullptr;
    }
}

char Board::getTurn(){
    return turn;
}

bool Board::setupCheck(){
    bool blackKing = false, whiteKing = false;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j] != nullptr){
                char piece = grid[i][j]->getType();
                if((piece == 'p' || piece == 'P') && (j == 0 || j == 7)) return false; //pawn on 1st or 8th rank
                else if(piece == 'K' && !whiteKing) whiteKing = true; //find kings
                else if(piece == 'k' && !blackKing) blackKing = true;
                else if(piece == 'K' && whiteKing) return false; //more than one king
                else if(piece == 'k' && blackKing) return false;
            }
        }
    }
    if(whiteKing && blackKing && !this->isCheck('w') && !this->isCheck('b')) return true;
    return false;
}

void Board::resetBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j]) delete(grid[i][j]);
            grid[i][j] = nullptr;
        }
    }
    turn = 'w';
}

Board::Board(){
    for(int i = 0; i < 8; i++){
        grid[i] = new Piece*[8];
    }

    turn = 'w';
};
Board::~Board(){
    for (auto piece : captured) {
        delete piece;
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j]) delete(grid[i][j]);
            grid[i][j] = nullptr;
        }
    }

};
