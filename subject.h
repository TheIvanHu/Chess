#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>

class Observer;

class Subject {
    std::vector<Observer*> observers;
public:
    void attach(Observer* o);
    void detach(Observer* o);
    virtual ~Subject();
protected:
    void notifyObservers();

}

#endif