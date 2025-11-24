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

	bool insertarL8(T destino);
	void mostrarLista();

	Tripla<T>* getPrimerAdyacente();
	Tripla<T>* getSiguienteAdyacente(Tripla<T>* actual);
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
bool Vertice<T>::insertarL8(T destino)
{
	return lista.InsertarFinal(destino);
}

template<typename T>
void Vertice<T>::mostrarLista()
{
	lista.Mostrar();
}

template<typename T>
inline Tripla<T>* Vertice<T>::getPrimerAdyacente()
{
	return lista.getPrimer();
}

template<typename T>
inline Tripla<T>* Vertice<T>::getSiguienteAdyacente(Tripla<T>* actual)
{
	return lista.SacarSiguienteAdyacente(actual);
}
