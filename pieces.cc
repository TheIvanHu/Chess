#include "pieces.h"
#include <string>

Rook::Rook(char c, coord pos);
void Rook::move(coord pos);
coord Rook::getPosition();
char Rook::getColor();
bool Rook::validMove(coord pos);
bool Rook::hasMoved();
void Rook::castle();
char Rook::getType();


King::King(char c, coord pos);
void King::move(coord pos);
coord King::getPosition();
char King::getColor();
bool King::validMove(coord pos);
bool King::hasMoved();
King::void castle();
King::char getType();


Pawn::Pawn(char c, coord pos);
void Pawn::move(coord pos);
coord Pawn::getPosition();
char Pawn::getColor();
bool Pawn::validMove(coord pos);
bool Pawn::hasMoved();
string Pawn::promote(std::string piece);
char Pawn::getType();

Bishop::Bishop(char c, coord pos);
void Bishop::move(coord pos);
coord Bishop::getPosition();
char Bishop::getColor();
bool Bishop::validMove(coord pos);
char Bishop::getType();


Knight::Knight(char c, coord pos);
void Knight::move(coord pos);
coord Knight::getPosition();
char Knight::getColor();
bool Knight::validMove(coord pos);
char Knight::getType();


Queen::Queen(char c, coord pos);
void Queen::move(coord pos);
coord Queen::getPosition();
char Queen::getColor();
bool Queen::validMove(coord pos);
char Queen::getType();

