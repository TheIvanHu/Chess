#ifndef __SUBJECT_H__
#define __SUBJECT_H__

class Subject;
class Board;

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
}

class TextObserver : Observer {
    Board subject;
public:
    void notify() override;
    TextObserver(Board subject);
    ~TextObserver();
}

class GraphicalObserver : Observer {
    Board subject;
public:
    void notify() override;
    GraphicalObserver(Board subject);
    ~GraphicalObserver();
}


#endif