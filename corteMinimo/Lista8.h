#pragma once
#include <iostream>
#include <string>
#include "Tripla.h"

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

	Tripla<T>* SacarSiguienteAdyacente(Tripla<T>* actual);
	Tripla<T>* getPrimer();
private:
	Tripla<T>* Primer;
	Tripla<T>* Ultimo;
};



template<typename T>
inline Lista8<T>::Lista8()
{
	Primer = nullptr;
	Ultimo = nullptr;
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
	if (Primer == nullptr) {// verifica si la lista esta vacia
		Primer = new Tripla<T>(nullptr, e, nullptr);
		Ultimo = Primer;
	}
	else {
		Primer = new Tripla<T>(nullptr, e,Primer);
		Primer->getSig()->setAnt(Primer);
	}
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
	return resultado;

}

template<typename T>
inline bool Lista8<T>::EliminarPrincipio()
{
	bool resultado = true;
	if (Primer == nullptr) {// lista vacia
		resultado = false;
	}
	else {
		if (Primer == Ultimo) { //verifica si hay un elemento 
			delete Primer;
			Primer = Ultimo = nullptr;
		}
		else {
			Primer = Primer->getSig();
			delete Primer->getAnt();
			Primer->setAnt(nullptr);
		}
	}
	return resultado;
}

template<typename T>
inline bool Lista8<T>::EliminarFinal()
{
	bool resultado = true;
	if (Ultimo == nullptr) {
		resultado = false; // lista vacía
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
			cout << "(" << letra << ", " << actual->getPeso() << ") ";
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
inline Tripla<T>* Lista8<T>::SacarSiguienteAdyacente(Tripla<T>* actual)
{
	Tripla<T>* res = actual;
	if (res == nullptr) {
		res = nullptr;
	}
	else {
		res = res->getSig();
	}
	return res;
}

template<typename T>
inline Tripla<T>* Lista8<T>::getPrimer()
{
	return Primer;
}
