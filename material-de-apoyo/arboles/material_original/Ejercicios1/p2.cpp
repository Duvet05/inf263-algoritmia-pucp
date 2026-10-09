#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;


bool esMenor(NodoArbol* ABB, int max) {
  if (ABB == nullptr)
    return true;

  if (ABB->elemento > max)
    return false;
  return esMenor(ABB->derecha, max);
}

bool esMayor(NodoArbol* ABB, int min) {

  if (ABB == nullptr)
    return true;

  if (ABB->elemento < min)
    return false;
  return esMayor(ABB->izquierda, min);
}

bool perteneceRango(ArbolBinario& ABB, int min, int max) {

  return esMayor(ABB.raiz, min) && esMenor(ABB.raiz, max);
}

int main() {

  ArbolBinarioBusqueda ABB;
  construir(ABB);

  insertar(ABB, 5);
  insertar(ABB, 1);
  insertar(ABB, 3);
  insertar(ABB, 4);
  insertar(ABB, 2);

  int min = 1;
  int max = 5;

  cout << perteneceRango(ABB.arbolBinario, min, max) << endl;

  return 0;
}