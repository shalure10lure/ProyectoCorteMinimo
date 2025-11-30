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
		Primer = new Tripla<T>(nullptr, e, Primer);
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
		Ultimo = new Tripla<T>(Ultimo, e, nullptr);
		Ultimo->getAnt()->setSig(Ultimo);
	}
	size++;
	return resultado;

}

template<typename T>
inline bool Lista8<T>::EliminarPrincipio()
{
	if (Primer == nullptr) {
		return false; // lista vacía
	}

	Tripla<T>* aEliminar = Primer;

	if (Primer == Ultimo) {
		// Solo hay un nodo
		Primer = Ultimo = nullptr;
	}
	else {
		// Más de un nodo
		Primer = Primer->getSig();
		Primer->setAnt(nullptr);
	}

	delete aEliminar;
	size--;
	return true;
}

template<typename T>
inline bool Lista8<T>::EliminarFinal()
{
	if (Ultimo == nullptr) return false; // lista vacía

	Tripla<T>* aEliminar = Ultimo;

	if (Primer == Ultimo) {
		// Solo hay un nodo
		Primer = Ultimo = nullptr;
	}
	else {
		Ultimo = Ultimo->getAnt();
		Ultimo->setSig(nullptr);
	}

	delete aEliminar;
	size--;
	return true;
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
			cout << "(" << letra << ") ";
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
		for (int i = 0; i < indice; i++) {
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
	Tripla<T>* actual = Primer;

	while (actual) {
		if (actual->getElem() == e) {
			// Nodo a eliminar
			if (actual == Primer) return EliminarPrincipio();
			if (actual == Ultimo) return EliminarFinal();

			// Nodo intermedio
			Tripla<T>* ant = actual->getAnt();
			Tripla<T>* sig = actual->getSig();

			ant->setSig(sig);
			sig->setAnt(ant);

			delete actual;
			size--;
			return true;
		}
		actual = actual->getSig();
	}

	return false; // no encontrado
}
