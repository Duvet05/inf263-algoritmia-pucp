#include "FuncionesPila.h"

namespace pilas {

void inicializar(Pila &pila) {
    listas::inicializar(pila.lista);
}

bool esPilaVacia(const Pila &pila) {
    return listas::esListaVacia(pila.lista);
}

int altura(const Pila &pila) {
    return listas::longitud(pila.lista);
}

void apilar(Pila &pila, const Elemento &dato) {
    listas::insertarInicio(pila.lista, dato);
}

bool desapilar(Pila &pila, Elemento &dato) {
    Nodo *nodo = listas::extraerInicio(pila.lista);
    if (nodo == nullptr) return false;
    dato = nodo->dato;
    delete nodo;
    return true;
}

const Elemento *cima(const Pila &pila) {
    if (esPilaVacia(pila)) return nullptr;
    return &pila.lista.inicio->dato;
}

Nodo *desapilarNodo(Pila &pila) {
    return listas::extraerInicio(pila.lista);
}

void apilarNodo(Pila &pila, Nodo *nodo) {
    listas::insertarNodoInicio(pila.lista, nodo);
}

// La lista guarda la cima primero; la recursion imprime la base antes.
static void imprimirDesdeBase(const Nodo *nodo, std::ostream &salida) {
    if (nodo == nullptr) return;
    imprimirDesdeBase(nodo->sig, salida);
    salida << ' ' << nodo->dato;
}

void imprimir(const Pila &pila, std::ostream &salida) {
    imprimirDesdeBase(pila.lista.inicio, salida);
}

void destruir(Pila &pila) {
    listas::destruir(pila.lista);
}

} // namespace pilas
