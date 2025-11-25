#pragma once
#include "Vertice.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

template <typename T>
struct Arista {
    T u, v;
    Arista(T _u, T _v) : u(_u), v(_v) {}
};

template <typename T>
class Grafo {
private:
    unordered_map<T, Vertice<T>> G;
    vector<Arista<T>> aristas_activas;

    bool eliminarAristaO1(int indice);
    void contraerArista(T u_id, T v_id);

public:
    Grafo() { srand(time(NULL)); }

    bool insertarArista(T u, T v);
    void seleccionarAristaAleatoria(T& u, T& v);
    int kargerContraccion();
    int kargerMinCut();
    void mostrarGrafo();
    void leerArchivo(string nombreArchivo);
};

template <typename T>
bool Grafo<T>::insertarArista(T u, T v) {
    if (u == v) return false;

    G[u].getLista().InsertarFinal(v);

    aristas_activas.push_back(Arista<T>(u, v));
    return true;
}

template <typename T>
bool Grafo<T>::eliminarAristaO1(int indice) {
    if (indice < 0 || indice >= (int)aristas_activas.size())
        return false;

    if (indice != aristas_activas.size() - 1)
        swap(aristas_activas[indice], aristas_activas.back());

    aristas_activas.pop_back();
    return true;
}

template <typename T>
void Grafo<T>::seleccionarAristaAleatoria(T& u, T& v) {
    if (aristas_activas.empty()) return;

    int pos = rand() % aristas_activas.size();

    u = aristas_activas[pos].u;
    v = aristas_activas[pos].v;
}
template<typename T>
inline void Grafo<T>::mostrarGrafo() {
    if (G.empty()) {
        cout << "El grafo está vacío." << endl;
        return;
    }
    for (auto& it : G) {
        cout << it.first << " = ";
        it.second.getLista().Mostrar();
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
void Grafo<T>::contraerArista(T u_id, T v_id) {
    auto& u_lista = G[u_id].getLista();
    auto& v_lista = G[v_id].getLista();

    // Mover adyacentes de v a u
    Tripla<T>* aux = v_lista.getPrimer();
    while (aux) {
        if (aux->getElem() != u_id) { // Evitar loop
            u_lista.InsertarFinal(aux->getElem());
        }
        aux = aux->getSig();
    }

    // Reemplazar todas las apariciones de v en otros vértices por u
    for (auto& par : G) {
        Tripla<T>* t = par.second.getLista().getPrimer();
        while (t) {
            if (t->getElem() == v_id) t->getElem() = u_id;
            t = t->getSig();
        }
    }
}

template<typename T>
int Grafo<T>::kargerContraccion() {
    while (G.size() > 2) {
        T u, v;
        seleccionarAristaAleatoria(u, v);
        contraerArista(u, v);

        // Eliminar v del grafo
        G.erase(v);

        // Eliminar la arista seleccionada
        for (int i = (int)aristas_activas.size() - 1; i >= 0; --i) {
            if ((aristas_activas[i].u == u && aristas_activas[i].v == v) ||
                (aristas_activas[i].u == v && aristas_activas[i].v == u)) {
                eliminarAristaO1(i);
            }
        }
    }

    // Contar aristas entre los dos vértices finales
    auto it = G.begin();
    Tripla<T>* aux = it->second.getLista().getPrimer();
    int count = 0;
    while (aux) { count++; aux = aux->getSig(); }
    return count;
}

template<typename T>
int Grafo<T>::kargerMinCut() {
    int N = max(30, (int)(G.size() * G.size() * log(max(2, (int)G.size()))));
    int best = INT_MAX;
    for (int i = 0; i < N; i++) {
        // Debes crear una copia del grafo y aristas_activas para cada iteración
        Grafo<T> copia = *this;
        int c = copia.kargerContraccion();
        if (c < best) best = c;
    }
    return best;
}
