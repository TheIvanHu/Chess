#include "board.h"
#include "subject.h"
#include "pieces.h"
#include <iostream>

void Board::move(coord start, coord end){
    Piece* p1 = grid[start.x][start.y];
    Piece* p2 = grid[start.x][start.y];
    if(p1 == nullptr || start.y < 0 || start.y > 7 || start.x < 0 || start.x > 7 || 
       ((start.x == end.x) && (start.y == end.y)) || !p1->validMove(end, grid) || p1->getColor() != turn){
        throw std::string("Invalid move."); //make error type
    }
    else if(p2 == nullptr){
        grid[end.x][end.y] = p1;
        grid[start.x][start.y] = nullptr;
    }
    else{
        //add undo part later
        grid[end.x][end.y] = p1;
        grid[start.x][start.y] = nullptr;
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

Piece* Board::findKing(){
    if(turn == 'w'){
        for(int i = 0; i < 8; i++){ //find black king
            for(int j = 0; j < 8; j++){
                Piece* p = grid[i][j];
                if(p->getColor() == 'b' && p->getType() == 'k'){
                    return p;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 8; i++){ //find white king
            for(int j = 0; j < 8; j++){
                Piece* p = grid[i][j];
                if(p->getColor() == 'w' && p->getType() == 'k'){
                    return p;
                }
            }
        }
    }
    return nullptr;
}
bool Board::isCheck(){
    Piece* king = findKing();
    for(int i = 0; i < 8; i++){ //check if anything can "take" the king
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            if(p != king && p->validMove(king->getPosition(), grid)){
                return true;
            }
        }
    }
    return false;
}

bool Board::isCheckmate(){
    Piece* king = findKing();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece* p = grid[i][j];
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    coord c{k,l};
                    if(p->validMove(c, grid)){ //check if the move is valid, then check if king is in check after the move
                        
                    }
                }
            }
        }
    }
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
