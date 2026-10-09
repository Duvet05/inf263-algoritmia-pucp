#include "arbol.h"
#include <iostream>
using namespace std;


bool esMenor(TNodoArbol* ABB, int max) {
  if (ABB == nullptr)
    return true;

  if (ABB->valor > max)
    return false;
  return esMenor(ABB->der, max);
}

bool esMayor(TNodoArbol* ABB, int min) {

  if (ABB == nullptr)
    return true;

  if (ABB->valor < min)
    return false;
  return esMayor(ABB->izq, min);
}

bool perteneceRango(TArbol ABB, int min, int max) {

  return esMayor(ABB, min) && esMenor(ABB, max);
}

int main() {

  TArbol ABB = nullptr;

  inserta_nodo(&ABB, 5);
  inserta_nodo(&ABB, 1);
  inserta_nodo(&ABB, 3);
  inserta_nodo(&ABB, 4);
  inserta_nodo(&ABB, 2);

  int min = 1;
  int max = 5;

  cout << perteneceRango(ABB, min, max) << endl;

  return 0;
}