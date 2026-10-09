#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

ArbolBinarioBusqueda construirABB(int *arreglo, int n) {

  ArbolBinarioBusqueda ABB;
  construir(ABB);

  for (int i=0; i<n; i++)
    insertar(ABB, arreglo[i]);

  return ABB;
}

int main() {

  int arreglo[] = {5, 2, 1, 3, 6, 7};

  ArbolBinarioBusqueda ABB = construirABB(arreglo, 6);

  recorrerEnOrden(ABB.arbolBinario);

  return 0;
}