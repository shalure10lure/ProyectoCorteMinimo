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
	void contraerVertices(T v1, T v2);
    pair<T, T> corteMinimo();
    pair<T, T> corteMinimoRepetido();
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





template<typename T>
void Grafo<T>::contraerVertices(T v1, T v2) {
    // 1. Tomamos todas las adyacencias de v1 y las agregamos a v2
    Tripla<T>* adyacente = vertices[v1].getPrimerAdyacente();
    while (adyacente != nullptr) {
        T elem = adyacente->getElem();
        if (elem != v2) { // Evitar auto-ciclos
            vertices[v2].insertarAdyacente(elem);
        }
        adyacente = adyacente->getSig();
    }

    for (auto& it : vertices) {
        Tripla<T>* actual = it.second.getPrimerAdyacente();
        while (actual != nullptr) {
            if (actual->getElem() == v1) {
                actual->setElem(v2); // Cambiamos la referencia al nuevo vértice
            }
            actual = actual->getSig();
        }
    }

    vertices.erase(v1);

    // 4. Actualizamos la lista de vértices disponibles
    vertices_disponibles.clear();
    for (auto& it : vertices) {
        vertices_disponibles.push_back(it.first);
    }
}
template<typename T>
pair<T, T> Grafo<T>::corteMinimo() {
    Grafo<T> copia = *this; // Hacemos una copia para no modificar el original

    while (copia.vertices.size() > 2) {
        T v1 = copia.elegirVerticeAleatorio();
        T v2 = copia.elegirAdyacenteAleatorio(v1);
        copia.contraerVertices(v1, v2);
    }

    auto it = copia.vertices.begin();
    T vert1 = it->first;
    it++;
    T vert2 = it->first;
    return { vert1, vert2 };
}
template<typename T>
pair<T, T> Grafo<T>::corteMinimoRepetido() {
    int N = vertices.size();
    int iteraciones = N * N * log(N); // según teoría de Karger
    int minCorte = INT_MAX;
    pair<T, T> mejorCorte;

    for (int i = 0; i < iteraciones; i++) {
        auto corte = corteMinimo();

        // Contamos cuántas aristas hay entre estos dos vértices
        int contador = 0;
        for (Tripla<T>* ady = vertices[corte.first].getSacarAdyacenteAleatorio(); ady != nullptr; ady = ady->getSig()) {
            if (ady->getElem() == corte.second)
                contador++;
        }

        if (contador < minCorte) {
            minCorte = contador;
            mejorCorte = corte;
        }
    }

    return mejorCorte;
}
