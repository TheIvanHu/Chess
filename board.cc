#include "board.h"
#include "subject.h"
#include "pieces.h"

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
    Piece* p = grid[pos.y][pos.x];
    return p->getType();
};

void Board::printBoard(){
    this->notifyObservers();
}
void Board::printResult(){
};

bool Board::isCheck(){
    Piece* king;
    if(whiteTurn){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Piece* p = grid[i][j];
                if(p->getColor() == 'b' && p->getType() == 'k'){
                    king = p;
                }
            }
        }
        
    }
    else{

    }
}

bool Board::isCheckmate(){
    
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
    grid = new Piece*[8][8];
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
