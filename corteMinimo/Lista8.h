#pragma once
#include "tripla.h"

template <typename T>
class Lista8 {
private:
    tripla<T>* Primer;
    tripla<T>* Ultimo;

public:
    Lista8() {
        Primer = nullptr;
        Ultimo = nullptr;
    }

    // --- NUEVO: Destructor ---
    // Necesario para liberar la memoria de los nodos al limpiar o destruir.
    ~Lista8() {
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            tripla<T>* siguiente = aux->getSig();
            delete aux;
            aux = siguiente;
        }
        Primer = Ultimo = nullptr;
    }

    // --- NUEVO: Constructor de Copia (Copia Profunda) ---
    Lista8(const Lista8& otra) : Primer(nullptr), Ultimo(nullptr) {
        tripla<T>* aux = otra.Primer;
        while (aux != nullptr) {
            // Usa InsertarFinal para crear NUEVOS nodos (copia profunda)
            InsertarFinal(aux->getElem());
            aux = aux->getSig();
        }
    }

    // --- NUEVO: Operador de Asignación ---
    Lista8& operator=(const Lista8& otra) {
        if (this != &otra) {
            // 1. Liberar los recursos de la lista actual (usando el destructor)
            this->~Lista8();

            // 2. Copiar los elementos de la otra lista
            tripla<T>* aux = otra.Primer;
            while (aux != nullptr) {
                InsertarFinal(aux->getElem());
                aux = aux->getSig();
            }
        }
        return *this;
    }
    // Dentro de la clase Lista8<T>
// TMerge() E O(1)
    void Merge(Lista8<T>& otraLista) {
        if (otraLista.Primer == nullptr) {
            // La otra lista está vacía, no hay nada que hacer.
            return;
        }

        if (this->Primer == nullptr) {
            // La lista actual está vacía, simplemente adoptamos los punteros de la otra.
            this->Primer = otraLista.Primer;
            this->Ultimo = otraLista.Ultimo;
        }
        else {
            // Conectamos el último nodo de la lista actual con el primer nodo de otraLista.
            this->Ultimo->setSig(otraLista.Primer);
            otraLista.Primer->setAnt(this->Ultimo);

            // El último nodo de la lista actual pasa a ser el último de la otra lista.
            this->Ultimo = otraLista.Ultimo;
        }

        // Desvinculamos la otra lista para evitar doble liberación de memoria (Double Free).
        otraLista.Primer = nullptr;
        otraLista.Ultimo = nullptr;
    }

    // Dentro de la clase Lista8<T>
// TReemplazar(N) E O(N)
    void Reemplazar(T valorAntiguo, T valorNuevo) {
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            if (aux->getElem() == valorAntiguo) {
                aux->setElem(valorNuevo);
            }
            aux = aux->getSig();
        }
    }

    // Dentro de la clase Lista8<T>
// TEliminarOcurrencias(N) E O(N)
    void EliminarOcurrencias(T el) {
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            if (aux->getElem() == el) {
                // Guardamos el siguiente antes de eliminar el nodo actual
                tripla<T>* sig = aux->getSig();

                // Lógica de eliminación (casi idéntica a la de EliminarDado, pero sin buscar)
                if (aux == Primer && aux == Ultimo) {
                    // Caso: Único elemento
                    delete aux;
                    Primer = Ultimo = nullptr;
                }
                else if (aux == Primer) {
                    // Caso: Primer elemento
                    Primer = aux->getSig();
                    Primer->setAnt(nullptr);
                    delete aux;
                }
                else if (aux == Ultimo) {
                    // Caso: Último elemento
                    Ultimo = aux->getAnt();
                    Ultimo->setSig(nullptr);
                    delete aux;
                }
                else {
                    // Caso: Elemento intermedio
                    aux->getAnt()->setSig(aux->getSig());
                    aux->getSig()->setAnt(aux->getAnt());
                    delete aux;
                }

                // Pasamos al siguiente elemento
                aux = sig;
            }
            else {
                // El elemento no coincide, pasamos al siguiente
                aux = aux->getSig();
            }
        }
    }

    // Dentro de la clase Lista8<T>
// TContarElementos(N) E O(N)
    int ContarElementos() {
        int contador = 0;
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            contador++;
            aux = aux->getSig();
        }
        return contador;
    }
    // TInsertarPrincipio()<=1+2+1<=4 E O(1)
    bool InsertarPrincipio(T el) {
        bool resp = true;
        if (Primer == nullptr) {
            Primer = new tripla<T>(nullptr, el, nullptr);
            Ultimo = Primer;
        }
        else {
            Primer = new tripla<T>(nullptr, el, Primer);
            Primer->getSig()->setAnt(Primer);
        }
        return resp;
    }

    // TInsertarFinal()<=1+3+1<=5 E O(1)
    bool InsertarFinal(T el) {
        bool resp = true;
        if (Ultimo == nullptr) {
            Ultimo = new tripla<T>(nullptr, el, nullptr);
            Primer = Ultimo;
        }
        else {
            tripla<T>* nuevo = new tripla<T>(Ultimo, el, nullptr);
            Ultimo->setSig(nuevo);
            Ultimo = nuevo;
        }
        return resp;
    }

    // TEliminarPrincipio()<= 1+1+1+1+1+1+1<=7 E O(1)
    bool EliminarPrincipio() {
        bool resp = false;
        if (Primer == nullptr) {
            cout << "Lista vacia" << endl;
        }
        else {
            tripla<T>* temp = Primer;
            Primer = Primer->getSig();
            if (Primer != nullptr) Primer->setAnt(nullptr);
            else Ultimo = nullptr;
            delete temp;
            resp = true;
        }
        return resp;
    }

    // TEliminarFinal()<=1+1+1+1+1+1+1<=7 E O(1)
    bool EliminarFinal() {
        bool resp = false;
        if (Ultimo == nullptr) {
            resp = false;
        }
        else {
            tripla<T>* temp = Ultimo;
            Ultimo = Ultimo->getAnt();

            if (Ultimo != nullptr)
                Ultimo->setSig(nullptr);
            else
                Primer = nullptr;

            delete temp;
            resp = true;
        }
        return resp;
    }

    // TMostrar(N)<= 1+N(2)+1<=2+2N
    //N=aux es la cantidad de nodos en la lista
    void Mostrar() {
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            cout << aux->getElem() << " <-> ";
            aux = aux->getSig();
        }
        cout << "NULL" << endl;
    }

    // TBuscarSecuencial(N)<=1+1+N(1+1)+1<=3+2N E O(N)
    //N=aux es la cantidad de nodos en la lista
    bool BuscarSecuencial(T el) {
        bool resp = false;
        tripla<T>* aux = Primer;
        while (aux != nullptr) {
            if (aux->getElem() == el) {
                resp = true;
            }
            aux = aux->getSig();
        }
        return resp;
    }

    // TBuscarRecursivo(N) E O(N)
    //N= es la cantidad de nodos en la lista
    bool BuscarRecursivo(T el, tripla<T>* Tnodo) {
        bool resp;
        if (Tnodo == nullptr) {
            resp = false;
        }
        else if (el == Tnodo->getElem()) {
            resp = true;
        }
        else {
            resp = BuscarRecursivo(el, Tnodo->getSig());
        }
        return resp;
    }

    tripla<T>* getPrimer() {
        return Primer;
    }

    // TEliminarDad(N) E O(N)
    //N= numero de nodos en la lista
    bool EliminarDado(T el) {
        bool resp = true;

        if (Primer == nullptr) {
            resp = false;
        }
        else {
            if (Primer == Ultimo) {
                if (Primer->getElem() == el) {
                    delete Primer;
                    Primer = Ultimo = nullptr;

                }
                else {
                    resp = false;
                }
            }
            else {
                tripla<T>* aux = Primer;
                while (aux != nullptr && aux->getElem() != el) {
                    aux = aux->getSig();
                }

                if (aux->getElem() == el) {
                    if (aux == Primer) {
                        resp = EliminarPrincipio();
                    }
                    else if (aux == Ultimo) {
                        resp = EliminarFinal();
                    }
                    else {
                        tripla<T>* anterior = aux->getAnt();
                        tripla<T>* siguiente = aux->getSig();
                        anterior->setSig(siguiente);
                        siguiente->setAnt(anterior);

                        delete aux;
                        resp = true;
                    }
                }
            }
        }

        return resp;
    }

};