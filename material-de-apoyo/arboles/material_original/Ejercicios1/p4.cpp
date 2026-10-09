#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

int hallarNumeroNiveles(NodoArbol* ABB) {
  
  if (ABB == nullptr)
    return 0;
  
  int izq = hallarNumeroNiveles(ABB->izquierda);
  int der = hallarNumeroNiveles(ABB->derecha);
  int max = izq > der ? izq : der;
  return 1 + max;
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

  cout << hallarNumeroNiveles(ABB.arbolBinario.raiz) << endl;
  return 0;
}