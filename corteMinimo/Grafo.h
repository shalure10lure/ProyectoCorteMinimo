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
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) { return (parent[x] == x) ? x : (parent[x] = find(parent[x])); }
    void unite(int x, int y) {
        int a = find(x), b = find(y);
        if (a == b) return;
        if (rank[a] < rank[b]) parent[a] = b;
        else { parent[b] = a; if (rank[a] == rank[b]) rank[a]++; }
    }
};
// Función auxiliar para elegir un elemento aleatorio
template<typename T>
T elegirDeVector(vector<T>& vec) {
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, vec.size() - 1);
    return vec[dist(rng)];
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
    //T elegirVerticeAleatorio();
    //void contraerVertices(T v1, T v2);

    // Devuelve los dos vértices finales y la cantidad de aristas
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
    if (vertices.find(Na) == vertices.end()) {
        vertices_disponibles.push_back(Na);
    }
    if (vertices.find(Nb) == vertices.end()) {
        vertices_disponibles.push_back(Nb);
    }
    vertices[Na].insertarAdyacente(Nb);
    vertices[Nb].insertarAdyacente(Na);
    cout << "Insertada arista: " << Na << " - " << Nb << endl;
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
int Grafo<T>::corteMinimoRapido() {
    int N = vertices_disponibles.size();
    if (N < 2) return 0;

    // Mapear vértices a índices 0..N-1
    unordered_map<T, int> indexMap;
    for (int i = 0; i < vertices_disponibles.size(); i++)
        indexMap[vertices_disponibles[i]] = i;

    // Generar lista de aristas
    vector<pair<int, int>> edges;
    for (auto& p : vertices) {
        int u = indexMap[p.first];
        for (T vT : p.second.getAdyacentes()) {
            int v = indexMap[vT];
            if (u < v) edges.push_back({ u,v }); // evitar duplicados
        }
    }

    if (edges.empty()) return 0;

    // Union-Find
    UnionFind uf(N);
    int comp = N;

    static mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<size_t> dist(0, edges.size() - 1);

    while (comp > 2) {
        auto e = edges[dist(rng)];
        int a = uf.find(e.first);
        int b = uf.find(e.second);
        if (a != b) {
            uf.unite(a, b);
            comp--;
        }
    }

    // Contar aristas cruzadas
    int corte = 0;
    for (auto& e : edges)
        if (uf.find(e.first) != uf.find(e.second))
            corte++;

    return corte;
}


// ===== Repetido varias veces =====
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
