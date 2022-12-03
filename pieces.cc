#include "pieces.h"
#include <iostream>
#include <string>

Piece::Piece(coord pos, char type, bool isWhite): pos{pos}, type{type}, isWhite{isWhite}{
};

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
    return a;
}

void Piece::move(coord p){
    pos = p;
}

coord Piece::getPosition(){
    return pos;
}

char Piece::getColor(){
    if(isWhite) return 'w';
    return 'b';
}

bool Piece::hasMoved(){
    return moved;
}

char Piece::getType(){
    return type;
}

void Piece::setMoved(bool m){
    moved = m;
}

Rook::Rook(bool w, coord pos): Piece{pos, 'r', w}{
    if(w){
        type = 'R';
    }
};

bool Rook::validMove(coord p, Piece *** grid){  
    if((p.x == pos.x)){
        for(int c = (min(p.y, pos.y)+1); c < max(p.y, pos.y); c++){
            if(grid[c][p.x]){
                return false;
            }
        }
        return true;
    }

    if((p.y == pos.y)){
        for(int c = (min(p.x, pos.x)+1); c < max(p.x, pos.x); c++){
            if(grid[p.y][c]){
                return false;
            }
        }
        return true;
    }
    return false;
}
        
void Rook::castle(){};
King::King(bool w, coord pos): Piece{pos, 'k', w}{
        if(w){
        type = 'K';
    }
};   
bool King::validMove(coord p, Piece *** grid){
    if((p.y == (pos.y + 1)||(p.y == (pos.y - 1)) || (p.y == pos.y)) && (p.x == (pos.x + 1)||(p.x == (pos.x - 1)) || (p.x == pos.x))) return true;
    return false;
};
void King::castle(){};


Pawn::Pawn(bool w, coord pos): Piece{pos, 'p', w}{
    if(w){
        type = 'P';
    }
};
bool Pawn::validMove(coord p, Piece *** grid){
    if(p.x == pos.x){
        if(grid[p.x][p.y]) return false;
        if(isWhite && ((p.y == (pos.y + 1)) || ((p.y == (pos.y + 2)) && (!moved)))) return true;
        if(!isWhite && ((p.y == (pos.y - 1)) || ((p.y == (pos.y - 2)) && (!moved)))) return true;
    }
    //capture
    if(grid[p.x][p.y]){
        if(isWhite && (p.y == (pos.y + 1)) && ((p.x == (pos.x + 1) || (p.x == (pos.x - 1))))) return true;
        if(!isWhite && (p.y == (pos.y - 1)) && ((p.x == (pos.x + 1) || (p.x == (pos.x - 1))))) return true;
    }
    return false;    
};
void Pawn::promote(std::string piece){}

Bishop::Bishop(bool w, coord pos): Piece{pos, 'b', w}{
    if(w){
        type = 'B';
    }
};
bool Bishop::validMove(coord p, Piece *** grid){
    int d = abs(p.x-pos.x);
    if((p.x-pos.x) == (p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(grid[min(p.x, pos.x) + c][min(p.y, pos.y) + c]){
                return false;
            }
        }
        return true;
    }
    
    if((p.x-pos.x) == -(p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(grid[min(p.x, pos.x) + c][max(p.y, pos.y) - c]){
                return false;
            }
        }
        return true;
    }
    return false;
};

Knight::Knight(bool w, coord pos): Piece{pos, 'n', w}{
    if(w){
        type = 'N';
    }
};
bool Knight::validMove(coord p, Piece *** grid){
    if((((p.x == (pos.x + 2)) || (p.x == (pos.x - 2))) && ((p.y == (pos.y +1)) || (p.y == (pos.y - 1)))) || 
    (((p.y == (pos.y + 2)) || (p.y == (pos.y - 2))) && ((p.x == (pos.x + 1)) || (p.x == (pos.x - 1))))) return true;
    
    return false;
}; 

Queen::Queen(bool w, coord pos): Piece{pos, 'q', w}{
    if(w){
        type = 'Q';
    }
};
bool Queen::validMove(coord p, Piece *** grid){
    //if(abs(p.x-pos.x) != abs(p.y-pos.y)) return false; 
    int d = abs(p.x-pos.x);

    if((p.x-pos.x) == (p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(grid[min(p.x, pos.x) + c][min(p.y, pos.y) + c]){
                return false;
            }
        }
        return true;
    }
    
    if((p.x-pos.x) == -(p.y-pos.y)){
        for(int c = 1; c < d; c++){
            if(grid[min(p.x, pos.x) + c][max(p.y, pos.y) - c]){
                return false;
            }
        }
        return true;
    }

    if((p.x == pos.x)){
        for(int c = (min(p.y, pos.y)+1); c < max(p.y, pos.y); c++){
            if(grid[p.x][c]){
                return false;
            }
        }
        return true;
    }

    if((p.y == pos.y)){
        for(int c = (min(p.x, pos.x)+1); c < max(p.x, pos.x); c++){
            if(grid[c][p.y]){
                return false;
            }
        }
        return true;
    }
    return false;
}
        