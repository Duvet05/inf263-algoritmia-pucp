

#ifndef FUNCIONESARBOLES_H
#define FUNCIONESARBOLES_H

#include "ArbolBinario.h"

void construir(struct ArbolBinario & );

bool esArbolVacio(const struct ArbolBinario & arbol);
bool esNodoVacio(struct NodoArbol * nodo);

struct NodoArbol * crearNuevoNodoArbol(struct NodoArbol *, int, 
                                                          struct NodoArbol *);
void plantarArbolBinario(struct ArbolBinario &, struct NodoArbol *, int,
                                                       struct NodoArbol * );
void plantarArbolBinario(struct ArbolBinario &, struct ArbolBinario &, int,
                                                struct ArbolBinario &);
int raiz(struct NodoArbol * nodo);
void imprimeRaiz(const struct ArbolBinario & arbol);
void imprimeNodo(struct NodoArbol * nodo);

struct  NodoArbol * hijoDerecho(const struct ArbolBinario &);
struct  NodoArbol * hijoIzquierdo(const struct ArbolBinario &);

void recorrerEnPreOrdenRecursivo(struct NodoArbol * nodo);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void recorrerEnPostOrdenRecursivo(struct NodoArbol * nodo);

void recorrerEnOrden(const struct ArbolBinario &);
void recorrerPreOrden(const struct ArbolBinario &);
void recorrerPostOrden(const struct ArbolBinario &);

int altura(const struct ArbolBinario &);
int alturaRecursivo(struct NodoArbol * nodo);

int numeroNodos(const struct ArbolBinario &);
int numeroNodosRecursivo(struct NodoArbol * nodo);

int numeroHojas(const struct ArbolBinario &);

int esEquilibrado(const struct ArbolBinario &);
int esEquilibradoRecursivo(struct NodoArbol * nodo);

int esHoja(const struct ArbolBinario &);

void destruirArbolBinario(struct ArbolBinario &);
void destruirRecursivo(struct NodoArbol *);

bool esABB(struct NodoArbol * nodo);

#endif /* FUNCIONESARBOLES_H */


