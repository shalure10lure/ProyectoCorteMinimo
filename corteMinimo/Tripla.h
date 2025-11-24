#pragma once
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Tripla
{
public:
	Tripla();
	Tripla(Tripla* a, T e, Tripla* s);
	~Tripla();
	Tripla* getSig();
	Tripla* getAnt();
	T getElem();
	void setSig(Tripla* s);
	void setAnt(Tripla* a);

private:
	Tripla* sig;
	Tripla* ant;
	T elem;
};

template<typename T>
inline Tripla<T>::Tripla()
{
	sig = nullptr;
	ant = nullptr;
}

template<typename T>
inline Tripla<T>::Tripla(Tripla* a, T e, Tripla* s)
{
	ant = a;
	elem = e;
	sig = s;
}

template<typename T>
inline Tripla<T>::~Tripla()
{
	sig = nullptr;
	ant = nullptr;
}

template<typename T>
inline Tripla<T>* Tripla<T>::getSig()
{
	return sig;
}

template<typename T>
inline Tripla<T>* Tripla<T>::getAnt()
{
	return ant;
}

template<typename T>
inline T Tripla<T>::getElem()
{
	return elem;
}

template<typename T>
inline void Tripla<T>::setSig(Tripla* s)
{
	sig = s;
}

template<typename T>
inline void Tripla<T>::setAnt(Tripla* a)
{
	ant = a;
}
