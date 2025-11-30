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
#include <random>


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

    void actualizarAristas(T u_id, T v_id);
    bool eliminarAristaO1(int indice);
    void contraerVertices(T u_id, T v_id);

public:
    Grafo() { srand(time(NULL)); }

    bool insertarArista(T u, T v);
    void seleccionarAristaAleatoria(T& u, T& v);
    int kargerContraccion();
    int kargerMinCut();
    void mostrarGrafo();
    bool leerArchivo(string nombreArchivo);
    size_t getNumeroVertices() const;
};

template<typename T>
void Grafo<T>::actualizarAristas(T u_id, T v_id) {
    // Itera sobre las aristas_activas y actualiza las que contienen a v_id
    for (size_t i = 0; i < aristas_activas.size(); ) {
        T& u_arista = aristas_activas[i].u;
        T& v_arista = aristas_activas[i].v;

        // 1. Actualizar el extremo v_id para que apunte al nuevo super-vértice u_id
        if (u_arista == v_id) {
            u_arista = u_id;
        }
        // Usar 'if' simple: Si la arista era (v, v), ambas se actualizarán a u, 
        // lo que es correcto antes de la eliminación del autociclo.
        // Mantenemos el 'if' simple como lo habías propuesto, pero aclaramos la lógica para la revisión de autociclos.
        if (v_arista == v_id) {
            v_arista = u_id;
        }

        // 2. Eliminar Auto-Ciclos (Aristas que ahora unen u_id consigo mismo)
        if (u_arista == v_arista) {
            // Se convierte en O(1) gracias a tu método eliminarAristaO1
            eliminarAristaO1(i);
            // ¡Importante! No incrementamos 'i' porque el elemento en la posición 'i'
            // fue reemplazado por el último elemento de la lista.
        }
        else {
            i++;
        }
    }
}

template<typename T>
bool Grafo<T>::eliminarAristaO1(int indice) {
    bool res = true;
    if (indice < 0 || indice >= (int)aristas_activas.size()) {
        res = false;
    }
    else {
        if (indice != aristas_activas.size() - 1) {
            swap(aristas_activas[indice], aristas_activas.back());
        }
        aristas_activas.pop_back();
        res = true;
    }
    return res;
}
template<typename T>
void Grafo<T>::contraerVertices(T u_id, T v_id) {
    // 0. Si v_id no existe, o si u_id y v_id son el mismo (ya contraídos/autociclo), salimos.
    if (G.find(v_id) == G.end() || u_id == v_id) return;

    // El vértice u_id debe existir. Si no existe, el algoritmo fallará.
    if (G.find(u_id) == G.end()) return;

    // --- Contracción Lógica ---

    // 1. Fusionar las listas de adyacencia (Mover adyacencias de v a u)
    G[u_id].getLista().Merge(G[v_id].getLista());

    // 2. Eliminar el vértice v del mapa G
    G.erase(v_id);

    // 3. Actualizar adyacencias en todo el grafo
    // Todos los vértices que apuntaban a v_id ahora deben apuntar a u_id.
    for (auto& par : G) {
        // No es necesario revisar if (par.first != u_id) porque G[u_id] no se está
        // reemplazando a sí mismo, y la lista de u_id se limpia en el paso 4.
        par.second.getLista().Reemplazar(v_id, u_id);
    }

    // 4. Eliminar autociclos en la nueva lista de adyacencia de u
    // Las aristas que eran (u, v) o (v, u) ahora son (u, u) en la lista de u.
    G[u_id].getLista().EliminarOcurrencias(u_id);

    // 5. Actualizar el contador de adyacentes del vértice contraído (u_id)
        // (O(Longitud de lista))
        // NOTA: Esta línea asume la existencia de G[u_id].setContAdy().
    G[u_id].setContAdy(G[u_id].getLista().ContarElementos());
}

template<typename T>
int Grafo<T>::kargerContraccion() {
    // El algoritmo se ejecuta mientras haya más de dos vértices
    while (G.size() > 2) {
        T u, v;

        // 1. Elegir uniformemente al azar una arista (u, v)
        seleccionarAristaAleatoria(u, v);

        // 2. Contrae v en u (convierte v en u)
        // IMPORTANTE: Primero actualiza todas las referencias de las aristas
        // para mantener la lista aristas_activas consistente.
        actualizarAristas(u, v);

        // 3. Contrae y fusiona el vértice v en u en la estructura del grafo.
        contraerVertices(u, v);
    }

    // Retornar la cuenta del corte representado por los 2 vértices finales
    // El tamaño final de aristas_activas (que ahora solo contiene aristas
    // entre los dos super-vértices restantes) es el valor del corte.
    return aristas_activas.size();
}

template<typename T>
int Grafo<T>::kargerMinCut() {
    int min_cut = -1;

    // Obtener el número inicial de vértices (N)
    int N = G.size();

    // Si hay menos de 2 vértices, el corte es 0.
    if (N < 2) return 0;


    // Usamos std::max(2.0, (double)N) para evitar log(1) o log(0).
    //int num_runs = (int)(N * N * std::log(std::max(2.0, (double)N)));
    int num_runs = N * N;
    // Para asegurar al menos un buen número de corridas si N es pequeño, N*N es un buen límite inferior.
    // Usaremos la versión simple y robusta:

    for (int i = 0; i < num_runs; ++i) {
        // 1. Crear una copia profunda del grafo actual.
        // **IMPORTANTE: Asume que se ha implementado el Constructor de Copia.**
        Grafo<T> copia_grafo = *this;

        // 2. Ejecutar la contracción en la copia.
        int current_cut = copia_grafo.kargerContraccion();

        // 3. Actualizar el corte mínimo.
        if (min_cut == -1 || current_cut < min_cut) {
            min_cut = current_cut;
        }
    }

    return min_cut;
}

template<typename T>
bool Grafo<T>::insertarArista(T u, T v) {
    bool respuesta = false;
    if (u == v) {
        respuesta = false;
    }
    else {
        if (G.find(u) == G.end()) G[u] = Vertice<T>();

        G[u].getLista().InsertarFinal(v);

        aristas_activas.push_back(Arista<T>(u, v));
        respuesta = true;
    }
    return respuesta;
}

template<typename T>
void Grafo<T>::seleccionarAristaAleatoria(T& u, T& v) {
    if (!aristas_activas.empty()) {

        // Reemplazo de rand(): generador moderno
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, static_cast<int>(aristas_activas.size()) - 1);

        int pos = dist(rng);   // índice aleatorio
        u = aristas_activas[pos].u;
        v = aristas_activas[pos].v;
    }
}

template<typename T>
void Grafo<T>::mostrarGrafo() {
    if (G.empty()) {
        cout << "El grafo está vacío." << endl;
        return;
    }
    for (auto& par : G) {
        cout << par.first << " = ";
        par.second.getLista().Mostrar();
    }
}

template <typename T>
bool Grafo<T>::leerArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) return false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        T u, v;
        ss >> u;

        while (ss >> v) {
            if (v == "-1") break;
            insertarArista(u, v);
        }
    }
    return true;
}

template <typename T>
size_t Grafo<T>::getNumeroVertices() const {
    return G.size();
}
