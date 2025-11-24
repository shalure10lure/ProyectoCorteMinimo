
#include <iostream>
#include "Grafo.h"
using namespace std;

int main()
{
    srand(time(NULL));

	Grafo<string> miGrafo;
    miGrafo.leerArchivo("grafo.txt");
    miGrafo.mostrarGrafo();
    for (int i = 0; i < 100; i++) {
        string v = miGrafo.elegirVerticeAleatorio();
        string u = miGrafo.elegirAdyacenteAleatorio(v);
        cout << "Vertice: " << v << " -> Adyacente : " << u << endl;
    }
}

