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
    T elegirDeVector(const vector<T>& vec);
    int corteMinimoRapido();
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
    // Crear Na si no existe
    if (vertices.find(Na) == vertices.end()) {
        vertices[Na] = Vertice<T>();
    }
    // Crear Nb si no existe
    if (vertices.find(Nb) == vertices.end()) {
        vertices[Nb] = Vertice<T>();
    }

    // Agregar a la lista de vértices disponibles si no está
    if (find(vertices_disponibles.begin(), vertices_disponibles.end(), Na) == vertices_disponibles.end())
        vertices_disponibles.push_back(Na);
    if (find(vertices_disponibles.begin(), vertices_disponibles.end(), Nb) == vertices_disponibles.end())
        vertices_disponibles.push_back(Nb);

    vertices[Na].insertarAdyacente(Nb);
}

template<typename T>
inline void Grafo<T>::mostrarGrafo() {
    if (vertices.empty()) {
        cout << "El grafo está vacío." << endl;
        return;
    }
    for (auto& it : vertices) {
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

// Elegir un elemento aleatorio de un vector
template<typename T>
T Grafo<T>::elegirDeVector(const vector<T>& vec) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, vec.size() - 1);
    return vec[dist(rng)];
}
template<typename T>
int Grafo<T>::corteMinimoRapido() {
    // --- 1️⃣ Copiamos el grafo original ---
    unordered_map<T, Vertice<T>> copia_vertices = vertices;
    vector<T> copia_lista = vertices_disponibles;

    static mt19937 rng(random_device{}());

    // --- 2️⃣ Mientras queden más de 2 vértices ---
    while (copia_lista.size() > 2) {
        // Elegir v1 aleatorio
        uniform_int_distribution<int> dist1(0, copia_lista.size() - 1);
        T v1 = copia_lista[dist1(rng)];

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

    // --- 7️⃣ Validar que queden exactamente 2 vértices ---
    if (copia_lista.size() != 2) {
        cerr << "Error: el grafo no tiene suficientes vértices conectados." << endl;
        return -1;
    }

    T a = copia_lista[0];
    T b = copia_lista[1];

    // --- 8️⃣ Contar aristas entre los 2 vértices finales ---
    int corte = 0;
    for (T x : copia_vertices[a].getAdyacentes()) {
        if (x == b) corte++;
    }

    // --- 9️⃣ Información para depuración ---
    cout << "Vértices finales: " << a << " y " << b << endl;
    cout << a << " tiene adyacentes: ";
    for (T x : copia_vertices[a].getAdyacentes()) cout << x << " ";
    cout << endl;

    return corte;
}

template<typename T>
int Grafo<T>::corteMinimoRepetido() {
    int N = vertices_disponibles.size();
    int iter = max(30, (int)(N * N * log(max(2, N))));
    int mejor = numeric_limits<int>::max();

    for (int i = 0;i < iter;i++) {
        int c = corteMinimoRapido();
        if (c < mejor) mejor = c;
    }
    return mejor;
}
