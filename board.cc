#include "board.h"
#include "subject.h"
#include "pieces.h"
#include <iostream>

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
    p1->move(end);
    grid[end.x][end.y] = p1;
    grid[start.x][start.y] = nullptr;
    if(p2 == nullptr){
        Move m{!p1->hasMoved(), start, end, false};
        moves.emplace_back(m);
    }
    else{
        captured.emplace_back(p2);
        Move m{!p1->hasMoved(), start, end, true};
        moves.emplace_back(m);
    }
    if(!p1->hasMoved()) p1->setMoved(true);
    
    if(this->getTurn() == 'w') this->setTurn('b');
    else this->setTurn('w');
    
    if(this->isCheck(((turn=='w')? 'b':'w'))){
        this->undo();
        throw std::string("This leaves your king in check.");
    }
    // if(this->isStalemate()){

    // }
    // else if(this->isCheckmate()){
        
    // }
    // if(this->isCheck()){
    //     if(turn == 'w') std::cout << "White is in check.";
    //     else std::cout << "Black is in check";
    // }
    
};

void Board::undo(){
    if(moves.size() == 0) return;
    
    Move m = moves.at(moves.size() - 1);
    moves.pop_back();

    Piece* p1 = grid[m.end.x][m.end.y];
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
    Piece* king = findKing(color);
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
                            catch(std::string error){

                            }

                            
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    coord c{k,l};
                    if(p->validMove(c, grid)){
                        return false;
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

Board::Board(){
    for(int i = 0; i < 8; i++){
        grid[i] = new Piece*[8];
    }

    turn = 'w';
};
Board::~Board(){
    for(int i = 0; i < 8; i++){
        delete [] grid[i];
    }
};
