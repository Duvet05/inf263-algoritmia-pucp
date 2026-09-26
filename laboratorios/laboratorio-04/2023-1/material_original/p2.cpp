#include "./ArbolesBinarios/funcionesArbolesBinarios.h"
#include "./ArbolesBinarios//funcionesArbolesBB.h"
#include <iostream>
using namespace std;
#include <climits>

struct NodoPila {
  NodoArbol* elemento;
  bool visitado = false;
  NodoPila* sig = nullptr;
};

struct Pila {
  NodoPila* inicio = nullptr;
  NodoPila* fin = nullptr;
};

void insertarEnPila(Pila& pila, NodoArbol* elemento) {
  if (elemento == nullptr)  
    return;
  
  NodoPila* nodo = new NodoPila;
  nodo->elemento = elemento;
  if (pila.fin != nullptr)
    pila.fin->sig = nodo;
  pila.fin = nodo;
  if (pila.inicio == nullptr)
    pila.inicio = pila.fin;
}

NodoArbol* removerDePila(Pila& pila) {
  if (pila.inicio == nullptr)
    return nullptr;

  NodoPila* nodo = pila.fin;
  if (pila.inicio == pila.fin) {
    pila.fin = nullptr;
    pila.inicio = nullptr;
  }

  else {
    NodoPila* nodo;
    for (nodo = pila.inicio; nodo->sig != pila.fin; nodo = nodo->sig);
    pila.fin = nodo;
    pila.fin->sig = nullptr;
  }

  NodoArbol* elemento = nodo->elemento;
  delete nodo;
  return elemento;
}


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

void preordenIterativo(ArbolBinarioBusqueda& arbol) {
  
  Pila pila;
  cout << endl;
  insertarEnPila(pila, arbol.arbolBinario.raiz);

  while (true) {

    if (pila.inicio == nullptr)
      break;

    NodoArbol* nodoArbol = pila.fin->elemento;

    if (nodoArbol->izquierda != nullptr &&
        pila.fin->visitado == false) {

      cout << nodoArbol->elemento << "\t";
      pila.fin->visitado = true;
      
      insertarEnPila(pila, nodoArbol->izquierda);
    }
    else {
      if (pila.fin->visitado == false)
        cout << nodoArbol->elemento << "\t";
      removerDePila(pila);
      insertarEnPila(pila, nodoArbol->derecha);
    }
    
  }
  cout << endl;
}

int main() {

  ArbolBinarioBusqueda destino;
  construir(destino.arbolBinario);
  
  insertar(destino, 5202);
  insertar(destino, 4001);
  insertar(destino, 2503);
  insertar(destino, 4202);
  insertar(destino, 6001);

  ArbolBinarioBusqueda emisor;
  construir(emisor.arbolBinario);

  insertar(emisor, 6501);
  insertar(emisor, 2501);
  insertar(emisor, 1202);
  insertar(emisor, 3401);
  insertar(emisor, 7502);
  insertar(emisor, 7001);

  recorrerEnPreOrdenRecursivo(destino.arbolBinario.raiz);
  cout << endl;
  recorrerEnPreOrdenRecursivo(emisor.arbolBinario.raiz);
  cout << endl;

  fusionar(destino, emisor.arbolBinario.raiz);

  recorrerEnPreOrdenRecursivo(destino.arbolBinario.raiz);

  preordenIterativo(destino);

  return 0;
}