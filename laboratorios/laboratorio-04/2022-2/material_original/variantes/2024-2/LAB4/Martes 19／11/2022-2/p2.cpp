#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;
#include <climits>

void insertarLote(NodoArbol*& nodo, int elemento) {

  if (nodo == nullptr) {
    nodo = crearNuevoNodoArbol(nullptr, elemento, nullptr);
    return;
  }

  if (elemento / 100 == nodo->elemento / 100) {
    int lote = elemento / 100;
    nodo->elemento = lote * 100 + (elemento % 100) + (nodo->elemento % 100); 
    return;
  }

  if (elemento < nodo->elemento)
    insertarLote(nodo->izquierda, elemento);
  else 
    insertarLote(nodo->derecha, elemento);
}

bool esNodoHoja(NodoArbol* nodo) {
  return nodo != nullptr && nodo->izquierda == nullptr && nodo->derecha == nullptr;
}

void fusionar(ArbolBinarioBusqueda &destino, NodoArbol*& emisor) {

  if (emisor == nullptr)
    return;
  
  if (esNodoHoja(emisor)) {
    int elemento = emisor->elemento;
    delete emisor;
    emisor = nullptr;
    cout << "Insertando " << elemento << endl;
    insertarLote(destino.arbolBinario.raiz, elemento);
    return;
  }

  fusionar(destino, emisor->izquierda);
  fusionar(destino, emisor->derecha);

  cout << "Insertando " << emisor->elemento << endl;
  insertarLote(destino.arbolBinario.raiz, emisor->elemento);
  delete emisor;
  emisor = nullptr;
}

int main() {

  ArbolBinarioBusqueda destino;
  construir(destino.arbolBinario);
  
  insertar(destino, 2018021120);
  insertar(destino, 2018040910);
  insertar(destino, 2017081020);
  insertar(destino, 2017062020);

  ArbolBinarioBusqueda emisor;
  construir(emisor.arbolBinario);

  insertar(emisor, 2018021105);
  insertar(emisor, 2017081110);
  insertar(emisor, 2018041015);

  recorrerEnOrden(destino.arbolBinario);
  cout << endl;
  recorrerEnOrden(emisor.arbolBinario);
  cout << endl;

  fusionar(destino, emisor.arbolBinario.raiz);

  recorrerEnOrden(destino.arbolBinario);

  return 0;
}

