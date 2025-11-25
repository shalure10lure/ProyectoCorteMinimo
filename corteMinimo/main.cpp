#include <iostream>
#include <chrono>
#include "Grafo.h"
using namespace std;
using namespace chrono;

int main() {
    Grafo<string> g;

    g.leerArchivo("grafo.txt");
    g.mostrarGrafo();

    auto inicio = high_resolution_clock::now();  // tiempo inicial

    int resultado = g.kargerMinCut();    // llamada a la función

    auto fin = high_resolution_clock::now();     // tiempo final

    // Diferencia en milisegundos
    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    cout << "Corte mínimo entre " << resultado<< " aristas" << endl;
    cout << "Tiempo de ejecución: " << duracion << " ms" << endl;
    
    return 0;
}
