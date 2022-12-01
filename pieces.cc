#include "pieces.h"
#include <string>

Piece::Piece(coord pos, char type, bool isWhite):: pos{pos}, type{type}, isWhite{isWhite}{};

int max(int a, int b){
    if(a < b) return b;
    return a;
}

int min(int a, int b){
    if(a < b) return a;
    return b;
}

int abs(int a){
    if(a < 0) return (-a);
}

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

char Piece::getType(){
    return type;
}

Rook::Rook(bool w, coord pos): Piece{pos, "r", w}{};
bool Rook::validMove(coord pos){
    //Check Boundaries
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if(p.x == pos.x && p.y == pos.y) return false;

    if((p.x == pos.x)){
        for(int c = (min(p.y, pos.y)+1); c < max(p.y, pos.y); c++){
            if(board[c][p.x]){
                return false;
            }
        }
        return true;
    }

    if((p.y == pos.y)){
        for(int c = (min(p.x, pos.x)+1); c < max(p.x, pos.x); c++){
            if(board[p.y][c]){
                return false;
            }
        }
        return true;
    }
    return false;
}
        
void Rook::castle();


King::King(bool w, coord pos): Piece{pos, "k", w}{
    //Check Boundaries
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    
};
bool King::validMove(coord p, Board * board){
    //Check Boundaries
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if(p.x == pos.x && p.y == pos.y) return false;

    if((p.y == (pos.y + 1)||(p.y == (pos.y - 1)) || (p.y == pos.y)) && (p.x == (pos.x + 1)||(p.x == (pos.x - 1)) || (p.x == pos.x))) return true;
    return false;
};
King::void castle();


Pawn::Pawn(bool w, coord pos): Piece{pos, "p", w}{};
bool Pawn::validMove(coord p, Board * board){
    //Check Boundaries
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if(p.x == pos.x && p.y == pos.y) return false;
    
    if(p.x == pos.x){
        if(board[p.y][p.x]) return false;
        if(isWhite && ((p.x == (pos.x - 1)) || ((p.x == (pos.x - 2)) && (!moved)))) return true;
        if(!isWhite && ((p.x == (pos.x + 1)) || ((p.x == (pos.x + 2)) && (!moved)))) return true;
    }
    //capture
    if(board[p.y][p.x]){
        if(isWhite && (p.x == (pos.x - 1)) && ((p.y == (pos.y + 1) || (p.y == (pos.y - 1))))) return true;
        if(!isWhite && (p.x == (pos.x + 1)) && ((p.y == (pos.y + 1) || (p.y == (pos.y - 1))))) return true;
    }
    return false;    
};
string Pawn::promote(std::string piece){}

Bishop::Bishop(bool w, coord pos): Piece{pos, "b", w}{};
bool Bishop::validMove(coord p, Board * board);{
     //Check Boundaries
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if(p.x == pos.x && p.y == pos.y) return false;

    int d = abs(p.x-pos.x);

    if((p.x-pos.x) == (p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(board[min(p.x, pos.x) + c][min(p.y, pos.y) + c]){
                return false;
            }
        }
        return true;
    }
    
    if((p.x-pos.x) == -(p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(board[min(p.x, pos.x) + c][max(p.y, pos.y) - c]){
                return false;
            }
        }
        return true;
    }
    return false;
};

Knight::Knight(bool w, coord pos): Piece{pos, "n", w}{};
bool Knight::validMove(coord p, Board * board){
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if((((p.x == (pos.x + 2)) || (p.x == (pos.x - 2))) && ((p.y == (pos.y +1)) || (p.y == (pos.y - 1)))) || 
    (((p.y == (pos.y + 2)) || (p.y == (pos.y - 2))) && ((p.x == (pos.x + 1)) || (p.x == (pos.x - 1))))) return true;
    
    return false;
}; 

Queen::Queen(bool w, coord pos): Piece{pos, "q", w}{};
bool Queen::validMove(coord p, Board * board){
    if((p.x < 0) || (p.x > 7) || (p.y < 0) || (p.y > 7)) return false;
    //Make sure one of same players pieces isn't already on that square
    if(board[p.y][p.x] && board[p.y][p.x]->getColor() == this->getcolor()) return false;
    //Make sure the target square isn't the square the piece is already on
    if(p.x == pos.x && p.y == pos.y) return false;
    //if(abs(p.x-pos.x) != abs(p.y-pos.y)) return false; 

    int d = abs(p.x-pos.x);

    if((p.x-pos.x) == (p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(board[min(p.x, pos.x) + c][min(p.y, pos.y) + c]){
                return false;
            }
        }
        return true;
    }
    
    if((p.x-pos.x) == -(p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(board[min(p.x, pos.x) + c][max(p.y, pos.y) - c]){
                return false;
            }
        }
        return true;
    }

    if((p.x == pos.x)){
        for(int c = (min(p.y, pos.y)+1); c < max(p.y, pos.y); c++){
            if(board[c][p.x]){
                return false;
            }
        }
        return true;
    }

    if((p.y == pos.y)){
        for(int c = (min(p.x, pos.x)+1); c < max(p.x, pos.x); c++){
            if(board[p.y][c]){
                return false;
            }
        }
        return true;
    }
    return false;
}
        