#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

int main() {
    Grafo<string> grafo;
    int opcion;
    string archivo;
    string u, v;

    do {
        cout << "\n==============================\n";
        cout << "         MENU GRAFO           \n";
        cout << "==============================\n";
        cout << "1. Leer grafo desde archivo\n";
        cout << "2. Insertar arista\n";
        cout << "3. Mostrar grafo\n";
        cout << "4. Ejecutar Karger (UNA Contraccion)\n";
        cout << "5. Ejecutar Karger (Min Cut - Repetido)\n";
        cout << "6. Seleccionar vertices aleatorios\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre del archivo: ";
            cin >> archivo;
            grafo.leerArchivo(archivo);
            break;

        case 2:
            cout << "Ingrese vertice U: ";
            cin >> u;
            cout << "Ingrese vertice V: ";
            cin >> v;
            grafo.insertarArista(u, v);
            cout << "Arista insertada.\n";
            break;

        case 3:
            grafo.mostrarGrafo();
            break;

        case 4: {
            int corte = grafo.corteMinimoRapido();
            cout << "--------------------------------\n";
            cout << "Corte minimo (UNA contraccion): " << corte << " aristas\n";
            cout << "--------------------------------\n";
            break;
        }

        case 5: {
            int corte = grafo.corteMinimoRepetido();
            cout << "--------------------------------\n";
            cout << "Corte minimo (Karger Repetido): " << corte << " aristas\n";
            cout << "--------------------------------\n";
            break;
        }

        case 6:
            grafo.funcionAzar();
            break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
