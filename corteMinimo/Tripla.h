#pragma once
#include <iostream>
using namespace std;

template <typename T>
class tripla {
private:
    tripla<T>* SIG;
    tripla<T>* ANT;
    T elem;

public:
    tripla(tripla<T>* a, T e, tripla<T>* s) {
        ANT = a;
        elem = e;
        SIG = s;
    }

    tripla<T>* getSig() { return SIG; }
    tripla<T>* getAnt() { return ANT; }
    T getElem() { return elem; }

    void setSig(tripla<T>* s) { SIG = s; }
    void setAnt(tripla<T>* a) { ANT = a; }
    void setElem(T e) { elem = e; }
};