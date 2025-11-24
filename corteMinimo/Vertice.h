#pragma once
#include <iostream>
#include <string>
#include "Lista8.h"

using namespace std;

template <typename T>
class Vertice
{
public:
	Vertice();
	~Vertice();
	void setPadre(T p);
	T getPadre();

	bool insertarAdyacente(T elemento);
	void mostrarLista();

	Tripla<T>* getSacarAdyacenteAleatorio();
private:
	Lista8<T> lista;
	T padre;
};
template<typename T>
Vertice<T>::Vertice()
{}

template<typename T>
Vertice<T>::~Vertice()
{}

template<typename T>
void Vertice<T>::setPadre(T p)
{
	padre = p;
}

template<typename T>
T Vertice<T>::getPadre()
{
	return padre;
}

template<typename T>
bool Vertice<T>::insertarAdyacente(T elemento)
{
	return lista.InsertarFinal(elemento);
}

template<typename T>
void Vertice<T>::mostrarLista()
{
	lista.Mostrar();
}


template<typename T>
inline Tripla<T>* Vertice<T>::getSacarAdyacenteAleatorio()
{
	return lista.sacarAdyacenteAleatorio();
}
