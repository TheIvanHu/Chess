#include "pieces.h"
#include <string>

Piece::Piece(coord pos, char type, bool isWhite):: pos{pos}, type{type}, isWhite{isWhite}{};

void Piece::move(coord p){
    pos = p;
}

coord Piece::getPosition(){
    return pos;
}

char Piece::getColor(){
    if(w) return "w";
    return "b";
}
bool Piece::hasMoved(){
    return moved;
}


Rook::Rook(bool w, coord pos): Piece{pos, "r", w}{};
bool Rook::validMove(coord pos){

}
void Rook::castle();


King::King(bool w, coord pos): Piece{pos, "k", w}{};
bool King::validMove(coord pos);
King::void castle();


Pawn::Pawn(bool w, coord pos): Piece{pos, "p", w}{};
bool Pawn::validMove(coord pos);
string Pawn::promote(std::string piece);

Bishop::Bishop(bool w, coord pos): Piece{pos, "b", w}{};
bool Bishop::validMove(coord pos, Board * board){

};

board[3,4] = new Pawn(true, p, pos, board)

Knight::Knight(bool w, coord pos): Piece{pos, "n", w}{};
bool Knight::validMove(coord pos, Board * board);


Queen::Queen(bool w, coord pos): Piece{pos, "q", w}{};
bool Queen::validMove(coord pos, Board * board);

