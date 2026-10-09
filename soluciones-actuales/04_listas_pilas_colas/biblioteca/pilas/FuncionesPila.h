#ifndef PILAS_FUNCIONES_PILA_H
#define PILAS_FUNCIONES_PILA_H

#include <iostream>
#include "../listas/FuncionesLista.h"

namespace pilas {

using listas::Elemento;
using listas::Nodo;

// La pila reutiliza una lista enlazada: la cima es el inicio de la lista,
// por eso apilar y desapilar cuestan O(1). Pasarla por referencia, nunca copiarla.
struct Pila {
    listas::Lista lista;
};

// Usar solo en una pila nueva o ya destruida. Para vaciar, usar destruir.
void inicializar(Pila &pila);
bool esPilaVacia(const Pila &pila);
int altura(const Pila &pila);

// Reserva un nodo nuevo en la cima.
void apilar(Pila &pila, const Elemento &dato);
// Copia la cima en dato y libera su nodo. Retorna false si la pila esta vacia.
bool desapilar(Pila &pila, Elemento &dato);
// Consulta la cima sin quitarla: nullptr si la pila esta vacia.
const Elemento *cima(const Pila &pila);

// Mueven nodos entre pilas sin new ni delete (util para Hanoi).
// desapilarNodo retorna nullptr si la pila esta vacia; quien recibe el nodo
// debe apilarlo en otra pila o liberarlo con delete.
Nodo *desapilarNodo(Pila &pila);
void apilarNodo(Pila &pila, Nodo *nodo); // nullptr no hace nada.

// Muestra los datos desde la base hasta la cima, cada uno precedido por un espacio.
void imprimir(const Pila &pila, std::ostream &salida = std::cout);
void destruir(Pila &pila);

} // namespace pilas

#endif
