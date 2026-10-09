#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;
#include <climits>

struct NodoCola {
  NodoArbol* elemento;
  bool visitado = false;
  NodoCola* sig = nullptr;
};

struct Cola {
  NodoCola* inicio = nullptr;
  NodoCola* fin = nullptr;
};

void insertarEnCola(Cola& cola, NodoArbol* elemento) {
  if (elemento == nullptr)  
    return;
  
  NodoCola* nodo = new NodoCola;
  nodo->elemento = elemento;
  if (cola.fin != nullptr)
    cola.fin->sig = nodo;
  cola.fin = nodo;
  if (cola.inicio == nullptr)
    cola.inicio = cola.fin;
}

NodoArbol* removerDeCola(Cola& cola) {
  if (cola.inicio == nullptr)
    return nullptr;

  NodoCola* nodo = cola.fin;
  if (cola.inicio == cola.fin) {
    cola.fin = nullptr;
    cola.inicio = nullptr;
  }

  else {
    NodoCola* nodo;
    for (nodo = cola.inicio; nodo->sig != cola.fin; nodo = nodo->sig);
    cola.fin = nodo;
    cola.fin->sig = nullptr;
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
  
  Cola cola;
  cout << endl;
  insertarEnCola(cola, arbol.arbolBinario.raiz);

  while (true) {

    if (cola.inicio == nullptr)
      break;

    NodoArbol* nodoArbol = cola.fin->elemento;

    if (nodoArbol->izquierda != nullptr &&
        cola.fin->visitado == false) {

      cout << nodoArbol->elemento << "\t";
      cola.fin->visitado = true;
      
      insertarEnCola(cola, nodoArbol->izquierda);
    }
    else {
      if (cola.fin->visitado == false)
        cout << nodoArbol->elemento << "\t";
      removerDeCola(cola);
      insertarEnCola(cola, nodoArbol->derecha);
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