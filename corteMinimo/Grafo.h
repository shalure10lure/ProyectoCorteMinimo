#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <random> 
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Vertice.h"
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
    T elegirDeVector( vector<T>& vec);
    void funcionazar();
    int corteMinimoRapido();
    int corteMinimoRepetido();

private:
    unordered_map<T, Vertice<T>> G;
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
    G[Na].insertarAdyacente(Nb);

    if (find(vertices_disponibles.begin(), vertices_disponibles.end(), Na) == vertices_disponibles.end()) {
        vertices_disponibles.push_back(Na);
    }
}

template<typename T>
inline void Grafo<T>::mostrarGrafo() {
    if (G.empty()) {
        cout << "El grafo esta vacio." << endl;
        return;
    }
    for (auto& it : G) {
        cout << it.first << " = ";
        for (T u : it.second.getAdyacentes())
            cout << u << " ";
        cout << endl;
    }
}

template<typename T>
inline void Grafo<T>::leerArchivo(string nomarchivo) {
    ifstream archivo(nomarchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
    }
    else {
        T vertice;

        while (archivo >> vertice) {
            T adyacente;
            while (archivo >> adyacente && adyacente != T("-1")) {
                insertarArista(vertice, adyacente);     
            }
        }
        archivo.close();
        cout << " Archivo abierto correctamente" << endl;
    }
}

template<typename T>
T Grafo<T>::elegirDeVector( vector<T>& vec) {
    T resultado = T();

    if (!vec.empty()) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, vec.size() - 1);
        int  indice = dist(rng);
        resultado = vec[indice];
    }
    return resultado;
}

template<typename T>
inline void Grafo<T>::funcionazar()
{
    T v1 = elegirDeVector(vertices_disponibles);
    T v2 = elegirDeVector(v1);
    cout << "azar v1: " << v1 << " --> azar v2 : "<<endl;
}

template<typename T>
int Grafo<T>::corteMinimoRapido() {
    // --- 1️⃣ Copiamos el grafo original ---
    unordered_map<T, Vertice<T>> copia_vertices = G;
    vector<T> copia_lista = vertices_disponibles;
    // --- 2️⃣ Mientras queden más de 2 vértices ---
    while (copia_lista.size() > 2) {
        // Elegir v1 aleatorio
        T v1 = elegirDeVector(copia_lista);

        auto& ady_v1 = copia_vertices[v1].getAdyacentes();
        if (ady_v1.empty()) {
            // v1 sin adyacentes, intentar otro vértice
            continue;
        }
        // Elegir v2 aleatorio entre los adyacentes
        T v2 = elegirDeVector(ady_v1);

        if (v1 == v2 || copia_vertices.find(v2) == copia_vertices.end()) {
            continue; // self-loop o v2 ya eliminado
        }
        // --- 3️⃣ CONTRACCIÓN: mover todos los adyacentes de v2 a v1 ---
        auto& ady_v2 = copia_vertices[v2].getAdyacentes();
        for (T vecino : ady_v2) {
            if (vecino != v1) {
                copia_vertices[v1].insertarAdyacente(vecino);
            }
        }
        // --- 4️⃣ Reemplazar v2 por v1 en todos los adyacentes ---
        for (auto& par : copia_vertices) {
            auto& ady = par.second.getAdyacentes();
            for (T& x : ady) {
                if (x == v2) x = v1;
            }
        }
        // --- 5️⃣ Eliminar self-loops de v1 ---
        auto& ady_final_v1 = copia_vertices[v1].getAdyacentes();
        ady_final_v1.erase(remove(ady_final_v1.begin(), ady_final_v1.end(), v1), ady_final_v1.end());
        // --- 6️⃣ Eliminar v2 del grafo y de la lista ---
        copia_vertices.erase(v2);
        copia_lista.erase(remove(copia_lista.begin(), copia_lista.end(), v2), copia_lista.end());
    }
    T a = copia_lista[0];
    T b = copia_lista[1];
    // --- 8️⃣ Contar aristas entre los 2 vértices finales ---
    int corte = 0;
    for (T x : copia_vertices[a].getAdyacentes()) {
        if (x == b) corte++;
    }

    return corte;
}

template<typename T>
int Grafo<T>::corteMinimoRepetido() {
    int N = vertices_disponibles.size();
    int iter = max(30, (int)(N * N * log(max(2, N))));
    int mejor = numeric_limits<int>::max();

    for (int i = 0;i < iter;i++) {
        int c = corteMinimoRapido();
        if (c < mejor) {
            mejor = c;
        } 
    }
    return mejor;
}
