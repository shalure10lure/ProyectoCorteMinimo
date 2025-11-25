#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Vertice.h"
using namespace std;

// Función auxiliar para elegir un elemento aleatorio de un vector
template<typename T>
T elegirDeVector(vector<T>& vec) {
    return vec[rand() % vec.size()];
}

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
    void contraerVertices(T v1, T v2);

    // Devuelve los dos vértices finales y la cantidad de aristas
    int corteMinimo();
    int corteMinimoRepetido();

private:
    unordered_map<T, Vertice<T>> vertices;
    vector<T> vertices_disponibles;
};

template<typename T>
inline Grafo<T>::Grafo() {
    srand(time(nullptr));
}

template<typename T>
inline Grafo<T>::~Grafo() {}

template<typename T>
inline void Grafo<T>::insertarArista(T Na, T Nb) {
    if (vertices.find(Na) == vertices.end()) {
        vertices_disponibles.push_back(Na);
    }
    if (vertices.find(Nb) == vertices.end()) {
        vertices_disponibles.push_back(Nb);
    }
    vertices[Na].insertarAdyacente(Nb);
    vertices[Nb].insertarAdyacente(Na);
}

template<typename T>
inline void Grafo<T>::mostrarGrafo() {
    for (auto& it : vertices) {
        cout << it.first << " = ";
        for (T u : it.second.getAdyacentes())
            cout << u << " ";
        cout << endl;
    }
}

#include <sstream>

template<typename T>
inline void Grafo<T>::leerArchivo(string nomarchivo) {
    ifstream archivo(nomarchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        T vertice;
        if (!(iss >> vertice)) continue;  // línea vacía

        T adyacente;
        while (iss >> adyacente) {
            if constexpr (std::is_same<T, string>::value) {
                if (adyacente == "-1") break;
            }
            else {
                if (adyacente == -1) break;
            }
            insertarArista(vertice, adyacente);
        }
    }

    archivo.close();
    cout << "Archivo abierto correctamente" << endl;
}


template<typename T>
inline T Grafo<T>::elegirVerticeAleatorio() {
    return elegirDeVector(vertices_disponibles);
}
template<typename T>
inline int Grafo<T>::corteMinimo() {
    if (vertices.size() <= 1) return 0;

    // Copia de adyacencias
    unordered_map<T, vector<T>> adyCopy;
    vector<T> vertsDisponibles;
    for (auto& v : vertices) {
        vertsDisponibles.push_back(v.first);
        adyCopy[v.first] = v.second.getAdyacentes();
    }

    while (vertsDisponibles.size() > 2) {
        T v1 = elegirDeVector(vertsDisponibles);
        vector<T>& adys = adyCopy[v1];
        if (adys.empty()) continue;

        T v2 = elegirDeVector(adys);
        if (v1 == v2) continue;

        // Fusionar adyacencias
        for (T u : adys) {
            if (u != v2) adyCopy[v2].push_back(u);
        }

        // Reemplazar referencias
        for (auto& p : adyCopy)
            for (T& u : p.second)
                if (u == v1) u = v2;

        // Eliminar auto-aristas
        adyCopy[v2].erase(remove(adyCopy[v2].begin(), adyCopy[v2].end(), v2), adyCopy[v2].end());

        // Borrar vértice
        adyCopy.erase(v1);
        vertsDisponibles.erase(remove(vertsDisponibles.begin(), vertsDisponibles.end(), v1), vertsDisponibles.end());
    }

    // Contar aristas entre los dos vértices finales
    T vA = vertsDisponibles[0];
    T vB = vertsDisponibles[1];
    int contador = 0;
    for (T u : adyCopy[vA])
        if (u == vB) contador++;

    return contador;
}
template<typename T>
inline int Grafo<T>::corteMinimoRepetido() {
    int N = vertices.size();
    int iteraciones = max(1, (int)(N * N * log(N)));
    int minAristas = INT_MAX;

    for (int i = 0; i < iteraciones; i++) {
        int corte = corteMinimo();
        if (corte < minAristas) minAristas = corte;
    }

    return minAristas;
}

