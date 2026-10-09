#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

struct NodoPila {
  int elemento;
  NodoPila* sig = nullptr;
};

struct Pila {
  NodoPila* cima = nullptr;
};  

void apilar(Pila& pila, int elemento) {
  NodoPila* nodo = new NodoPila;
  nodo->elemento = elemento;
  nodo->sig = pila.cima;
  pila.cima = nodo;
}

int desapilar(Pila& pila) {

  if (pila.cima == nullptr)
    return -1;

  NodoPila* nodo = pila.cima;
  pila.cima = nodo->sig;
  int elemento = nodo->elemento;
  delete nodo;
  return elemento;
}

bool hallarCaminoEntreNodos(Pila& pila, NodoArbol* origen, NodoArbol* destino) {

  if (origen == nullptr)
    return false;

  if (origen == destino) {
    apilar(pila, origen->elemento);
    return true;
  }

  bool izq = hallarCaminoEntreNodos(pila, origen->izquierda, destino);
  if (izq) {
    apilar(pila, origen->elemento);
    return true;
  }
  else {
    bool der = hallarCaminoEntreNodos(pila, origen->derecha, destino);
    if (der) {
      apilar(pila, origen->elemento);
      return true;
    }
  }
  return false;
}

int main() {

  ArbolBinarioBusqueda ABB;
  construir(ABB);

  insertar(ABB, 5);
  insertar(ABB, 1);
  insertar(ABB, 3);
  insertar(ABB, 4);
  insertar(ABB, 2);
  insertar(ABB, 6);

  Pila pila;

  if (hallarCaminoEntreNodos(pila, ABB.arbolBinario.raiz, ABB.arbolBinario.raiz->izquierda->derecha->izquierda)) {

    for (NodoPila* nodo = pila.cima; nodo != nullptr; nodo = nodo->sig)
      cout << nodo->elemento << " ";
    cout << endl;
  }

  return 0;
}