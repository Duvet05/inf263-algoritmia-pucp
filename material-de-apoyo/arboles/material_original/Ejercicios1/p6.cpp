#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

NodoArbol* espejo(NodoArbol* nodo) {

  if (nodo == nullptr)
    return nullptr;
  
  ArbolBinario arbol;
  construir(arbol);
  plantarArbolBinario(arbol, espejo(nodo->derecha), nodo->elemento, espejo(nodo->izquierda));

  return arbol.raiz;
}

int main() {

  ArbolBinarioBusqueda ABB;
  construir(ABB);

  insertar(ABB, 4);
  insertar(ABB, 2);
  insertar(ABB, 1);
  insertar(ABB, 3);
  insertar(ABB, 5);

  NodoArbol* raiz = espejo(ABB.arbolBinario.raiz);

  ArbolBinario arbol;
  construir(arbol);
  arbol.raiz = raiz;
  recorrerEnOrden(arbol);


  return 0;
}