#pragma once
#include "Lista8.h"

template <typename T>
class Vertice {
private:
    Lista8<T> lista; // Lista de adyacencia o elementos del vertice
    int contAdy;     // Contador de adyacentes

public:
    Vertice() { contAdy = 0; }

    // --- NUEVO: Constructor de Copia ---
    Vertice(const Vertice& otro)
        // Llama implícitamente al constructor de copia de Lista8 para 'lista'.
        // Copia superficial de 'contAdy' (que es un entero).
        : lista(otro.lista), contAdy(otro.contAdy) {
    }

    // --- NUEVO: Operador de Asignación ---
    Vertice& operator=(const Vertice& otro) {
        if (this != &otro) {
            // Llama al operador de asignación de Lista8 (copia profunda)
            lista = otro.lista;
            contAdy = otro.contAdy;
        }
        return *this;
    }

    void setContAdy(int c) { contAdy = c; }
    int getContAdy() const { return contAdy; }

    Lista8<T>& getLista() { return lista; }

};



