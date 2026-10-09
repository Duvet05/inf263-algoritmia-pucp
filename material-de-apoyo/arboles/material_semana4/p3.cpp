#include "arbol.h"
#include <iostream>
using namespace std;

bool buscarRecursivo(TNodoArbol* ABB, int n) {
  if (ABB == nullptr)
    return false;
  if (ABB->valor == n)
    return true;
  return buscarRecursivo(ABB->izq, n) || buscarRecursivo(ABB->der, n);
} 

bool seRepite(TNodoArbol* ABB, int n) {
  if (ABB == nullptr)
    return false;
  // Se asume que los elementos repetidos se insertan en
  // el hijo más a la izquierda del hijo derecho
  NodoArbol* nodo = ABB->der;
  return buscarRecursivo(nodo, n);
} 

bool seRepiteAlgunNumero(TNodoArbol* ABB) {
  if (ABB == nullptr)
    return false;
  return seRepite(ABB, ABB->valor) ||
    seRepiteAlgunNumero(ABB->izq) ||
    seRepiteAlgunNumero(ABB->der);
}

int main() {

  TArbol ABB = nullptr;

  inserta_nodo(&ABB, 5);
  inserta_nodo(&ABB, 1);
  inserta_nodo(&ABB, 3);
  inserta_nodo(&ABB, 4);
  inserta_nodo(&ABB, 2);
  inserta_nodo(&ABB, 6);
  inserta_nodo(&ABB, 1);

  cout << seRepiteAlgunNumero(ABB) << endl;

  return 0;
}

