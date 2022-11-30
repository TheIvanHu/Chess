#include "subject.h"
#include "observer.h"
#include <vector>
void Subject::attach(Observer *o){
    observers.push_back(o);
};

void Subject::detach(Observer *o){
    for(auto it = observers.begin(); it != observers.end(); it++){
        if(*it == o){
            observers.erase(it, observers.end());
        }
    }
};

void Subject::notifyObservers(){
    for(auto o: observers){
        o->notify();
    }
};

Subject::~Subject(){
    for(auto o : observers){
        delete o;
    }
}
