#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Vertice.h"
#define TAM 10
using namespace std;

template <typename T>
class Grafo
{
public:
    Grafo();
    ~Grafo();
    void insertarArista(T Na, T Nb);
    void mostrarGrafo();
    void leerArchivo(string nomarchivo);
    int ContarAristas();
private:
    unordered_map<T, Vertice<T>> vertices;
};

template<typename T>
inline Grafo<T>::Grafo()
{
}

template<typename T>
inline Grafo<T>::~Grafo()
{
}
template<typename T>
inline void Grafo<T>::insertarArista(T Na, T Nb)
{
    vertices[Na].insertarL8(Nb);
}

template<typename T>
inline void Grafo<T>::mostrarGrafo()
{
    for (auto& it : vertices) {
        cout << it.first << " = ";
        it.second.mostrarLista();
    }
}

template<typename T>
inline void Grafo<T>::leerArchivo(string nomarchivo) {
    ifstream archivo(nomarchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
    }
    else {
        string a, b;
        int c;
        while (archivo >> a >> b >> c) {
            insertarArista(a, b, c);
        }
        archivo.close();
        cout << " archivo abierto correctamente" << endl;
    }
}

template<typename T>
int Grafo<T>::ContarAristas() {
    int A = 0;
    for (auto& it : vertices) {
        T origen = it.first;
        Tripla<T>* ady = it.second.getPrimerAdyacente();
        while (ady != nullptr) {
            T destino = ady->getElem();
            if (origen < destino) {
                A++;
            }
            ady = ady->getSig();
        }
    }
    return A;
}
