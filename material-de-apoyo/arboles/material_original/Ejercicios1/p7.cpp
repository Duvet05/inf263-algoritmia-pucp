#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

NodoArbol* duplicado(NodoArbol* nodo) {

  if (nodo == nullptr)
    return nullptr;

  ArbolBinarioBusqueda arbol;
  construir(arbol);

  NodoArbol* nuevoNodo = crearNuevoNodoArbol(duplicado(nodo->izquierda), nodo->elemento, nullptr);

  plantarArbolBinario(arbol.arbolBinario, nuevoNodo, nodo->elemento, duplicado(nodo->derecha));

  return arbol.arbolBinario.raiz;
}


int main() {

  ArbolBinarioBusqueda ABB;
  construir(ABB);

  insertar(ABB, 2);
  insertar(ABB, 1);
  insertar(ABB, 3);

  NodoArbol* raiz = duplicado(ABB.arbolBinario.raiz);

  ArbolBinario arbol;
  construir(arbol);
  arbol.raiz = raiz;
  recorrerEnOrden(arbol);

  return 0;
}