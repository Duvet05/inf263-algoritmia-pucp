#include "arbol.h"
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

bool hallarCaminoEntreNodos(Pila& pila, TNodoArbol* origen, TNodoArbol* destino) {

  if (origen == nullptr)
    return false;

  if (origen == destino) {
    apilar(pila, origen->valor);
    return true;
  }

  bool izq = hallarCaminoEntreNodos(pila, origen->izq, destino);
  if (izq) {
    apilar(pila, origen->valor);
    return true;
  }
  else {
    bool der = hallarCaminoEntreNodos(pila, origen->der, destino);
    if (der) {
      apilar(pila, origen->valor);
      return true;
    }
  }
  return false;
}

int main() {

  TArbol ABB = nullptr;

  inserta_nodo(&ABB, 5);
  inserta_nodo(&ABB, 1);
  inserta_nodo(&ABB, 3);
  inserta_nodo(&ABB, 4);
  inserta_nodo(&ABB, 2);
  inserta_nodo(&ABB, 6);

  Pila pila;

  if (hallarCaminoEntreNodos(pila, ABB, ABB->izq->der->der)) {

    for (NodoPila* nodo = pila.cima; nodo != nullptr; nodo = nodo->sig)
      cout << nodo->elemento << " ";
    cout << endl;
  }

  return 0;
}