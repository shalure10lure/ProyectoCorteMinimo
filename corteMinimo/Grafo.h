#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdlib> 
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
    T elegirVerticeAleatorio();
    T elegirAdyacenteAleatorio(T vertice);
private:
    unordered_map<T, Vertice<T>> vertices;
    vector<T> vertices_disponibles;
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
    if (vertices.find(Na) == vertices.end()) {
        vertices_disponibles.push_back(Na);
    }
    vertices[Na].insertarAdyacente(Nb);
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
        string vertice;
        
        while (archivo >> vertice) {
            T adyacente;
            while (archivo>>adyacente) {
                if (adyacente != "-1") {
                    insertarArista(vertice, adyacente);
                }
                else {
                    break;
                }
            }
        }
        archivo.close();
        cout << " Archivo abierto correctamente" << endl;
    }
}

template<typename T>
inline T Grafo<T>::elegirVerticeAleatorio()
{
    int i = rand() % vertices_disponibles.size();
    return vertices_disponibles[i];
}

template<typename T>
inline T  Grafo<T>::elegirAdyacenteAleatorio(T vertice)
{
    Tripla<T>* adyacente = vertices[vertice].getSacarAdyacenteAleatorio();
    T resultado;
    if (adyacente != nullptr) {
        resultado=adyacente->getElem();
    }
    else {
        resultado = nullptr;
    }
    return resultado;
}




