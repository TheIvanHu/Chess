#include "computer.h"
#include "board.h"
#include "pieces.h"
#include <vector>
#include <string>

using namespace std;

void Computer1::move(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    try{
                        b->move(coord{i,j}, coord{k,l});
                        b->undo();
                        allValidMoves.push_back(to_string(i) + to_string(j) + to_string(k) + to_string(l));


                    }catch(string error){

                    }
                }
            }
        }
    }

    int r = rand() % allValidMoves.size();
    string m = allValidMoves[r];
    b->move(coord{m.at(0), m.at(1)}, coord{m.at(2), m.at(3)});
}