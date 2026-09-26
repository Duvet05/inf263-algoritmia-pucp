#include "./ArbolBinarioBusqueda/ArbolBinarioBusqueda/BibliotecaArbolBinarioBusqueda/funcionesArbolBinarioBusqueda.h"
#include "./ArbolBinarioBusqueda/ArbolBinarioBusqueda/BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"

#include <iostream>
#include <climits>
using namespace std;


void insertarLote(NodoArbolBinarioBusqueda*& nodo, int elemento) {

  if (nodo == nullptr) {
    NodoArbolBinarioBusqueda* nuevoNodo = new NodoArbolBinarioBusqueda;
    nuevoNodo->elemento.numero = elemento;
    nuevoNodo->izquierda = nullptr;
    nuevoNodo->derecha = nullptr;

    nodo = nuevoNodo;
    return;
  }

  if (elemento / 100 == nodo->elemento.numero / 100) {
    int lote = elemento / 100;
    nodo->elemento.numero = lote * 100 + (elemento % 100) + (nodo->elemento.numero % 100); 
    return;
  }

  if (elemento < nodo->elemento.numero)
    insertarLote(nodo->izquierda, elemento);
  else 
    insertarLote(nodo->derecha, elemento);
}

bool esNodoHoja(NodoArbolBinarioBusqueda* nodo) {
  return nodo != nullptr && nodo->izquierda == nullptr && nodo->derecha == nullptr;
}

void fusionar(ArbolBinarioBusqueda &destino, NodoArbolBinarioBusqueda*& emisor) {

  if (emisor == nullptr)
    return;
  
  if (esNodoHoja(emisor)) {
    int elemento = emisor->elemento.numero;
    // delete emisor;
    emisor = nullptr;
    cout << "Insertando " << elemento << endl;
    insertarLote(destino.raiz, elemento);
    return;
  }

  fusionar(destino, emisor->izquierda);
  fusionar(destino, emisor->derecha);

  cout << "Insertando " << emisor->elemento.numero << endl;
  insertarLote(destino.raiz, emisor->elemento.numero);
  // delete emisor;
  emisor = nullptr;
}

int main() {

  ArbolBinarioBusqueda destino;
  construir(destino);
  
  insertar(destino, {2018021120});
  insertar(destino, {2018040910});
  insertar(destino, {2017081020});
  insertar(destino, {2017062020});

  ArbolBinarioBusqueda emisor;
  construir(emisor);

  insertar(emisor, {2018021105});
  insertar(emisor, {2017081110});
  insertar(emisor, {2018041015});

  recorrerEnOrden(destino);
  cout << endl;
  recorrerEnOrden(emisor);
  cout << endl;

  fusionar(destino, emisor.raiz);

  recorrerEnOrden(destino);

  return 0;
}

