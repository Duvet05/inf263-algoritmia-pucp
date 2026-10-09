#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

int descendientes(NodoArbol* nodo) {

  if (nodo == nullptr)
    return 0;

  int izq = descendientes(nodo->izquierda);
  int der = descendientes(nodo->derecha);

  if (izq > der)
    cout << nodo->elemento << "(I) "; 
  else if (izq < der)
    cout << nodo->elemento << "(D) ";
  else 
    cout << nodo->elemento << "(*) ";
  
  return izq + der + 1;
}

int main() {

  ArbolBinarioBusqueda a;
  construir(a);
  insertar(a, 5);
  insertar(a, 2);
  insertar(a, 1);
  insertar(a, 3);
  insertar(a, 6);
  insertar(a, 7);

  descendientes(a.arbolBinario.raiz); 

  return 0;
}
