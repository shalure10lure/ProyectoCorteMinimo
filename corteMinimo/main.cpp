
#include <iostream>
#include "Grafo.h"
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

	Grafo<string> grafo;
    grafo.leerArchivo("grafo.txt");
    //grafo.mostrarGrafo();
    /*
    for (int i = 0; i < 1000; i++) {
        string v = miGrafo.elegirVerticeAleatorio();
        string u = miGrafo.elegirAdyacenteAleatorio(v);
        cout << "Vertice: " << v << " -> Adyacente : " << u << endl;
    }*/

    auto corte = grafo.corteMinimoRepetido();
    cout << "Corte mínimo entre: " << corte.first << " y " << corte.second << endl;

}

