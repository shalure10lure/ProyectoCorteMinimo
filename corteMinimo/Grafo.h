#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <set>
#include <numeric>
#include <random>
#include "Vertice.h"

using namespace std;

/* ============================
   UNION-FIND
============================ */
class UnionFind {
public:
    vector<int> parent, size;

    UnionFind(int n = 0) { init(n); }

    void init(int n) {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return (parent[x] == x) ? x : parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

/* ============================
      GRAFO TEMPLATE
============================ */
template <typename T>
class Grafo {
public:
    Grafo();
    ~Grafo();
    void insertarArista(T, T);
    void mostrarGrafo();
    void leerArchivo(string);

    int corteMinimoRapido();
    int corteMinimoRepetido();

private:
    unordered_map<T, Vertice<T>> vertices;
    vector<T> vertices_disponibles;

    unordered_map<T, int> nameToId;
    vector<T> idToName;
    vector<pair<int, int>> edges;

    int N;
};

template<typename T>
inline Grafo<T>::Grafo() : N(0) {}

template<typename T>
inline Grafo<T>::~Grafo() {}

/* Guardar en estructura original (tu lista enlazada) */
template<typename T>
inline void Grafo<T>::insertarArista(T a, T b)
{
    if (vertices.find(a) == vertices.end())
        vertices_disponibles.push_back(a);

    vertices[a].insertarAdyacente(b);
}

template<typename T>
inline void Grafo<T>::mostrarGrafo()
{
    for (auto& it : vertices) {
        cout << it.first << " = ";
        it.second.mostrarLista();
    }
}

/* ============================
        LEER ARCHIVO
============================ */
template<typename T>
inline void Grafo<T>::leerArchivo(string nomarchivo)
{
    ifstream archivo(nomarchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    set<T> allNames;
    unordered_map<T, vector<T>> temp_adj;

    T v, u;
    while (archivo >> v)
    {
        vector<T> adys;
        while (archivo >> u && u != "-1") {
            adys.push_back(u);
            allNames.insert(v);
            allNames.insert(u);
        }
        temp_adj[v] = adys;
    }
    archivo.close();

    // IDs
    idToName.assign(allNames.begin(), allNames.end());
    N = idToName.size();
    nameToId.clear();
    for (int i = 0; i < N; i++)
        nameToId[idToName[i]] = i;

    // Estructura original y edges
    edges.clear();
    for (auto& p : temp_adj) {
        for (auto& x : p.second) {
            insertarArista(p.first, x);

            int u = nameToId[p.first];
            int v = nameToId[x];
            if (u != v) {
                if (u < v) edges.emplace_back(u, v);
                else       edges.emplace_back(v, u);
            }
        }
    }

    // Quitar duplicados en edges
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    cout << "Grafo cargado: V=" << N << " E=" << edges.size() << endl;
}


/* ============================
   KARGER RÁPIDO UNA VEZ
============================ */
template<typename T>
int Grafo<T>::corteMinimoRapido()
{
    if (N < 2) return 0;
    if (edges.empty()) return 0;

    UnionFind uf(N);
    int comp = N;

    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, edges.size() - 1);

    while (comp > 2)
    {
        auto& e = edges[dist(rng)];
        int a = uf.find(e.first);
        int b = uf.find(e.second);

        if (a != b) {
            uf.unite(a, b);
            comp--;
        }
    }

    int corte = 0;
    for (auto& e : edges)
        if (uf.find(e.first) != uf.find(e.second))
            corte++;

    return corte;
}


/* ============================
   REPETIDO K VECES
============================ */
template<typename T>
int Grafo<T>::corteMinimoRepetido()
{
    int iter = max(30, (int)(N * N * log(max(2, N))));
    int mejor = INT_MAX;

    for (int i = 0; i < iter; i++) {
        int c = corteMinimoRapido();
        if (c < mejor)
            mejor = c;
    }
    return mejor;
}

