#include "arbol.h"
#include <iostream>
using namespace std;

int hallarNumeroNiveles(TNodoArbol* ABB) {
  
  if (ABB == nullptr)
    return 0;
  
  int izq = hallarNumeroNiveles(ABB->izq);
  int der = hallarNumeroNiveles(ABB->der);
  int max = izq > der ? izq : der;
  return 1 + max;
}

int main() {

  TArbol ABB = nullptr;

  inserta_nodo(&ABB, 5);
  inserta_nodo(&ABB, 1);
  inserta_nodo(&ABB, 3);
  inserta_nodo(&ABB, 4);
  inserta_nodo(&ABB, 2);
  inserta_nodo(&ABB, 6);

  cout << hallarNumeroNiveles(ABB) << endl;
  return 0;
}