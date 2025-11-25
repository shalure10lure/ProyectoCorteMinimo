#pragma once
#include <iostream>
#include <string>
#include "Tripla.h"
#include <cstdlib> 

using namespace std;

template <typename T>
class Lista8
{
public:
	Lista8();
	~Lista8();
	bool InsertarPrincipio(T e);
	bool InsertarFinal(T e);
	bool EliminarPrincipio();
	bool EliminarFinal();
	void Mostrar();
	bool BuscarRecursivo(T e, Tripla<T>* t);
	bool buscarecursivoelemento(T e);
	bool EliminarDado(T e);
	Tripla<T>* sacarAdyacenteAleatorio();
	int getSize();
	Tripla<T>* getPrimer();

private:
	Tripla<T>* Primer;
	Tripla<T>* Ultimo;
	int size;  
};

template<typename T>
inline Lista8<T>::Lista8()
{
	Primer = nullptr;
	Ultimo = nullptr;
	size = 0;
}

template<typename T>
inline Lista8<T>::~Lista8()
{
	while (Primer != nullptr) {
		EliminarPrincipio();
	}
}

template<typename T>
inline bool Lista8<T>::InsertarPrincipio(T e)
{
	bool resultado = true;
	if (Primer == nullptr) {
		Primer = new Tripla<T>(nullptr, e, nullptr);
		Ultimo = Primer;
	}
	else {
		Primer = new Tripla<T>(nullptr, e,Primer);
		Primer->getSig()->setAnt(Primer);
	}
	size++;
	return resultado;
}

template<typename T>
inline bool Lista8<T>::InsertarFinal(T e)
{
	bool resultado = true;
	if (Primer == nullptr) {
		Primer = new Tripla<T>(nullptr, e, nullptr);
		Ultimo = Primer;
	}
	else {
		Ultimo = new Tripla<T>(Ultimo, e,nullptr);
		Ultimo->getAnt()->setSig(Ultimo);
	}
	size++;
	return resultado;

}

template<typename T>
inline bool Lista8<T>::EliminarPrincipio()
{
	bool resultado = true;
	if (Primer == nullptr) {
		resultado = false;
	}
	else {
		if (Primer == Ultimo) { 
			delete Primer;
			Primer = Ultimo = nullptr;
		}
		else {
			Primer = Primer->getSig();
			delete Primer->getAnt();
			Primer->setAnt(nullptr);
		}
		size--;
	}
	return resultado;
}

template<typename T>
inline bool Lista8<T>::EliminarFinal()
{
	bool resultado = true;
	if (Ultimo == nullptr) {
		resultado = false;
	}
	else {
		if (Primer == Ultimo) {
			delete Ultimo;
			Primer = Ultimo = nullptr;
		}
		else {
			Ultimo = Ultimo->getAnt();
			delete Ultimo->getSig();
			Ultimo->setSig(nullptr);
		}
		size--;
	}
	return resultado;
}

template<typename T>
inline void Lista8<T>::Mostrar()
{
	if (Primer == nullptr) {
		cout << "Lista vacia" << endl;
	}
	else {
		Tripla<T>* actual = Primer;
		while (actual != nullptr) {
			string letra = actual->getElem();
			cout << "(" << letra << ") " ;
			actual = actual->getSig();
		}
		cout << endl;
	}
}

template<typename T>
inline bool Lista8<T>::BuscarRecursivo(T e, Tripla<T>* t)
{
	bool respuesta = true;
	if (t == nullptr) {
		respuesta = false;
	}
	else {
		if (e == t->getElem()) {
			respuesta = true;
		}
		else {
			respuesta = BuscarRecursivo(e, t->getSig());
		}
	}
	return respuesta;
}

template<typename T>
inline bool Lista8<T>::buscarecursivoelemento(T e)
{
	return BuscarRecursivo(e, Primer);
}

template<typename T>
inline Tripla<T>* Lista8<T>::sacarAdyacenteAleatorio()
{
	Tripla<T>* actual = Primer;
	if (size != 0) {
		int indice = rand() % size;
		for (int i = 0;i < indice;i++) {
			actual = actual->getSig();
		}
	}
	return actual;
}


template<typename T>
inline int Lista8<T>::getSize()
{
	return size;
}
template<typename T>
Tripla<T>* Lista8<T>::getPrimer() {
	return Primer;
}


template<typename T>
inline bool Lista8<T>::EliminarDado(T e)
{
	bool respuesta = true;

	if (Primer == nullptr) {
		respuesta = false;
	}
	else {
		if (Primer == Ultimo) {
			if (e == Primer->getElem()) {
				delete Primer;
				Primer = Ultimo = nullptr;
			}
			else {
				respuesta = false;
			}
		}
		else {
			Tripla<T>* aux = Primer;
			while (aux != Ultimo && aux->getElem() != e) {
				aux = aux->getSig();
			}
			if (aux->getElem() == e) {
				//Controlar si no es primero ni ultimo
				if (aux->getAnt() == nullptr) {
					EliminarPrincipio();
				}
				else {
					if (aux->getSig() == nullptr) {
						EliminarFinal();
					}
					else {//si esta en el medio se borra y el anterior le ponemos el valor del siguiente, y al diguiente del anterior
						Tripla<T>* anterior = aux->getAnt();
						Tripla<T>* siguiente = aux->getSig();
						anterior->setSig(siguiente);
						siguiente->setAnt(anterior);
						delete aux;
					}
				}
			}
			else {
				respuesta = false;
			}
		}
	}
	return respuesta;
}