#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

bool buscarRecursivo(NodoArbol* ABB, int n) {

  if (ABB == nullptr)
    return false;

  if (ABB->elemento == n)
    return true;

  return buscarRecursivo(ABB->izquierda, n) || buscarRecursivo(ABB->derecha, n);
} 

bool seRepite(NodoArbol* ABB, int n) {
  if (ABB == nullptr)
    return false;
  // Se asume que los elementos repetidos se insertan en el hijo más a la izquierda del hijo derecho
  NodoArbol* nodo = ABB->derecha;
/*   while (nodo != nullptr) {
    if (nodo->elemento == ABB->elemento)
      return true;
    nodo = nodo->izquierda;
  } */
  return buscarRecursivo(nodo, n);
} 

bool seRepiteAlgunNumero(NodoArbol* ABB) {
  if (ABB == nullptr)
    return false;
  return seRepite(ABB, ABB->elemento) ||
    seRepiteAlgunNumero(ABB->izquierda) ||
    seRepiteAlgunNumero(ABB->derecha);
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
  //insertar(ABB, 5);

  cout << seRepiteAlgunNumero(ABB.arbolBinario.raiz) << endl;

  return 0;
}

