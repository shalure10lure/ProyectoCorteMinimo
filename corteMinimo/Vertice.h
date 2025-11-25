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

	void insertarAdyacente(T elemento);
	void mostrarAdyacentes();

	T AdyacenteAleatorio();
	vector<T>& getAdyacentes();
private:
	vector<T> adyacentes;
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
inline void Vertice<T>::insertarAdyacente(T elemento)
{
	adyacentes.push_back(elemento);
}

template<typename T>
inline void Vertice<T>::mostrarAdyacentes()
{
	for (T v : adyacentes) cout << v << " ";
	cout << endl;
}

template<typename T>
inline T Vertice<T>::AdyacenteAleatorio()
{
	if (adyacentes.empty()) return T();
	return adyacentes[rand() % adyacentes.size()];
}

template<typename T>
inline vector<T>& Vertice<T>::getAdyacentes()
{
	return adyacentes;
}



