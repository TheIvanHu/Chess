#include "board.h"
#include "subject.h"
#include "piece.h"

void Board::move(coord start, coord end){

};
void Board::setTurn(char turn){
    whiteTurn = turn;
};
char Board::getState(coord pos){
    Piece* p = grid[pos.y][pos.x];
    p->getType();
};
void Board::printResult(){
    
};
Board::Board(){
    grid = new Piece*[8][8];
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
