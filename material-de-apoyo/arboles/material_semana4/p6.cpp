#include "arbol.h"
#include <iostream>
using namespace std;

TNodoArbol* espejo(TNodoArbol* nodo) {

  if (nodo == nullptr)
    return nullptr;
  
  TNodoArbol* arbol = new TNodoArbol;
  arbol->valor = nodo->valor;
  arbol->izq = espejo(nodo->der);
  arbol->der = espejo(nodo->izq);

  return arbol;
}

int main() {

  TArbol ABB = nullptr;

  inserta_nodo(&ABB, 4);
  inserta_nodo(&ABB, 2);
  inserta_nodo(&ABB, 1);
  inserta_nodo(&ABB, 3);
  inserta_nodo(&ABB, 5);

  NodoArbol* raiz = espejo(ABB);

  en_orden(raiz);

  return 0;
}