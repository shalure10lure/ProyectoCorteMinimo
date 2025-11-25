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
#include <numeric>  // Para iota

using namespace std;

// Union-Find con path compression y union by size
class UnionFind {
public:
    vector<int> parent, size;
    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (size[px] < size[py]) swap(px, py);
        parent[py] = px;
        size[px] += size[py];
        return true;
    }
};

template <typename T>
class Grafo
{
public:
    Grafo();
    ~Grafo();
    void insertarArista(int a, int b);
    void mostrarGrafo();
    void leerArchivo(string nomarchivo);
    int corteMinimo();  // Devuelve el número de aristas en el corte mínimo
    int corteMinimoRepetido();  // Devuelve el mínimo corte encontrado
private:
    unordered_map<T, int> id;
    vector<T> names;
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;  // Lista de aristas para selección rápida
    int N;
};

template<typename T>
inline Grafo<T>::Grafo() : N(0) {}

template<typename T>
inline Grafo<T>::~Grafo() {}

template<typename T>
inline void Grafo<T>::insertarArista(int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}

template<typename T>
inline void Grafo<T>::mostrarGrafo()
{
    for (int i = 0; i < N; i++) {
        cout << names[i] << " = ";
        for (int j : adj[i]) {
            cout << names[j] << " ";
        }
        cout << endl;
    }
}

template<typename T>
inline void Grafo<T>::leerArchivo(string nomarchivo) {
    ifstream archivo(nomarchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    unordered_map<T, vector<T>> temp_adj;
    set<T> vertices_set;
    string vertice;
    while (archivo >> vertice) {
        T adyacente;
        vector<T> ady_list;
        while (archivo >> adyacente) {
            if (adyacente != "-1") {
                ady_list.push_back(adyacente);
                vertices_set.insert(vertice);
                vertices_set.insert(adyacente);
            }
            else {
                break;
            }
        }
        temp_adj[vertice] = ady_list;
    }
    archivo.close();

    N = vertices_set.size();
    names.assign(vertices_set.begin(), vertices_set.end());
    for (int i = 0; i < N; i++) {
        id[names[i]] = i;
    }

    adj.assign(N, vector<int>());
    for (auto& p : temp_adj) {
        int u = id[p.first];
        for (T v_str : p.second) {
            int v = id[v_str];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        auto it = unique(adj[i].begin(), adj[i].end());
        adj[i].resize(it - adj[i].begin());
    }

    // Construir lista de aristas para selección uniforme
    edges.clear();
    for (int u = 0; u < N; u++) {
        for (int v : adj[u]) {
            if (u < v) {  // Evitar duplicados
                edges.emplace_back(u, v);
            }
        }
    }
    cout << "Archivo abierto correctamente. N=" << N << ", E=" << edges.size() << endl;
}

template<typename T>
int Grafo<T>::corteMinimo() {
    UnionFind uf(N);
    vector<pair<int, int>> active_edges = edges;  // Copia de aristas activas

    int num_components = N;  // Número inicial de componentes
    while (num_components > 2) {
        if (active_edges.empty()) break;  // Evitar loop infinito si no hay aristas
        // Elegir arista aleatoria
        int idx = rand() % active_edges.size();
        pair<int, int> e = active_edges[idx];
        int u = e.first, v = e.second;
        active_edges.erase(active_edges.begin() + idx);

        int pu = uf.find(u), pv = uf.find(v);
        if (pu == pv) continue;  // Ya conectados

        // Contraer: fusionar pu y pv
        uf.unite(pu, pv);
        num_components--;  // Reducir número de componentes
    }

    // Contar el corte: aristas que cruzan entre las dos componentes finales
    int corte = 0;
    for (auto& e : edges) {  // Usar la lista original de aristas
        int pu = uf.find(e.first), pv = uf.find(e.second);
        if (pu != pv) {
            corte++;  // Esta arista cruza el corte
        }
    }
    return corte;
}

template<typename T>
int Grafo<T>::corteMinimoRepetido() {
    int iteraciones = N * N * (int)log(N) + 1;  // Según teoría de Karger
    int minCorte = INT_MAX;

    for (int i = 0; i < iteraciones; i++) {
        int corte = corteMinimo();
        if (corte < minCorte && corte != INT_MAX) {  // Evitar tomar INT_MAX como mínimo
            minCorte = corte;
        }
    }
    return minCorte;
}


