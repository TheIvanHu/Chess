#include "board.h"
#include "subject.h"
#include "pieces.h"
#include <iostream>

void Board::move(coord start, coord end){
    Piece* p1 = grid[start.y][start.x];
    Piece* p2 = grid[start.y][start.x];
    if(p1 == nullptr || start.y <= -1 || start.y >= 8 || start.x <= -1 || start.x >= 8 || 
       ((start.x == end.x) && (start.y == end.y)) || !p1->validMove(end, grid)){
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
};

void Board::setTurn(char turn){
    whiteTurn = turn;
};

char Board::getState(coord pos){
    Piece* p = grid[pos.x][pos.y];
    return p->getType();
};

void Board::printBoard(){
    this->notifyObservers();
}
void Board::printResult(){
    double whiteScore = whiteWins + 0.5 * draws;
    double blackScore = blackWins + 0.5 * draws;
    std::cout << "Final Score:" << std::endl << "White: " << whiteScore << std::endl << "Black: " << blackScore;
};
Piece* Board::findKing(){
    if(whiteTurn){
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

Board::Board(){
    for(int i = 0; i < 8; i++){
        grid[i] = new Piece*[8];
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            grid[i][j] = nullptr;
        }
    }
    whiteTurn = true;
    whiteWins = 0;
    blackWins = 0;
    draws = 0;
};
Board::~Board(){
    for(int i = 0; i < 8; i++){
        delete [] grid[i];
    }
};
