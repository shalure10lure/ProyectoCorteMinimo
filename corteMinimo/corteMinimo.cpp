#include <iostream>
#include"Grafo.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    Grafo<string> grafo;
    grafo.leerArchivo("grafo.txt");   // cargar datos primero
    grafo.funcionazar();          // ahora sí tiene sentido
    //grafo.leerArchivo("g1.txt");
    //grafo.mostrarGrafo();
    //int corte = grafo.corteMinimoRepetido();
    //cout << "Corte mínimo: " << corte << endl;
    return 0;
}
