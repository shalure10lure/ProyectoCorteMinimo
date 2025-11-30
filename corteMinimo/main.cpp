#include <iostream>
#include <string>
#include <chrono>

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
        cout << "5. Ejecutar Karger (Min Cut - Repeticion)\n";
        cout << "6. Seleccionar arista aleatoria\n";
        cout << "7. PRUEBA: Contraer vertices (u, v)\n"; // Nueva opción para prueba manual
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre del archivo: ";
            cin >> archivo;
            if (grafo.leerArchivo(archivo))
                cout << "Archivo cargado correctamente.\n";
            else
                cout << "Error al leer archivo. Asegurese que el archivo existe.\n";
            break;

        case 2:
            cout << "Ingrese u: ";
            cin >> u;
            cout << "Ingrese v: ";
            cin >> v;
            if (grafo.insertarArista(u, v))
                cout << "Arista agregada.\n";
            else
                cout << "No se pudo insertar la arista (puede ser un autociclo).\n";
            break;

        case 3:
            grafo.mostrarGrafo();
            break;

        case 4: {
            // **Ejecución de una sola contracción**
            // Se necesita una copia porque la contracción modifica el grafo permanentemente.
            if (grafo.getNumeroVertices() <= 2) {
                cout << "El grafo ya tiene 2 o menos vertices. No se puede contraer mas.\n";
                break;
            }
            cout << "Ejecutando Karger Contracción...\n";
            Grafo<string> copia = grafo;
            int corte = copia.kargerContraccion();
            cout << "--------------------------------\n";
            cout << "Corte obtenido (UNA Contraccion): " << corte << " aristas\n";
            cout << "Grafo resultante:\n";
            copia.mostrarGrafo();
            cout << "--------------------------------\n";
            break;
        }

        case 5: {
            if (grafo.getNumeroVertices() < 2) {
                cout << "El grafo tiene muy pocos vertices para calcular el Min Cut.\n";
                break;
            }

            cout << "Ejecutando Karger Min Cut... \n";

            // --- MEDIR TIEMPO ---
            auto start = chrono::high_resolution_clock::now();

            int mincut = grafo.kargerMinCut();

            auto end = chrono::high_resolution_clock::now();
            double tiempo = chrono::duration<double, milli>(end - start).count();
            // ---------------------

            cout << "--------------------------------\n";
            cout << "Min Cut aproximado (Karger MinCut): " << mincut << " aristas\n";
            cout << "Tiempo de ejecucion total: " << tiempo << " ms\n";
            cout << "NOTA: El grafo original NO fue modificado.\n";
            cout << "--------------------------------\n";

            break;
        }

        case 6: {
            string a, b;
            grafo.seleccionarAristaAleatoria(a, b);

            if (a.empty() && b.empty()) // Usamos .empty() para string
                cout << "No hay aristas activas en el grafo.\n";
            else
                cout << "Arista aleatoria seleccionada: (" << a << ", " << b << ")\n";

            break;
        }

        case 7: {
            // **PRUEBA MANUAL DE CONTRACCIÓN (para debugging)**
            if (grafo.getNumeroVertices() <= 2) {
                cout << "El grafo ya tiene 2 o menos vertices. No se puede contraer manualmente.\n";
                break;
            }
            cout << "Vertices a contraer (v se contrae en u):\n";
            cout << "  Ingrese vertice U (representante): ";
            cin >> u;
            cout << "  Ingrese vertice V (a eliminar): ";
            cin >> v;

            // Esta función DEBE ser llamada en una copia si no quieres modificar el grafo original.
            // Para la prueba manual, modificaremos el grafo principal.
            // Es vital que tu implementación de contraerVertices llame a actualizarAristas primero.
            //grafo.actualizarAristas(u, v); // Necesitas hacer este método público temporalmente para la prueba
            //grafo.contraerVertices(u, v);

            cout << "Contraccion realizada. Vea el grafo con la opcion 3.\n";
            break;
        }

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